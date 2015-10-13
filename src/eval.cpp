#include <assert.h>
#include "rodent.h"
#include "eval.h"

static const int max_phase = 24;
const int phase_value[7] = { 0, 1, 1, 2, 4, 0, 0 };

static const U64 bbQSCastle[2] = { SqBb(A1) | SqBb(B1) | SqBb(C1) | SqBb(A2) | SqBb(B2) | SqBb(C2),
                                   SqBb(A8) | SqBb(B8) | SqBb(C8) | SqBb(A7) | SqBb(B7) | SqBb(C7)
                                 };
static const U64 bbKSCastle[2] = { SqBb(F1) | SqBb(G1) | SqBb(H1) | SqBb(F2) | SqBb(G2) | SqBb(H2),
                                   SqBb(F8) | SqBb(G8) | SqBb(H8) | SqBb(F7) | SqBb(G7) | SqBb(H7)
                                 };

static const U64 bbCentralFile = FILE_C_BB | FILE_D_BB | FILE_E_BB | FILE_F_BB;

U64 bbPawnTakes[2];
U64 bbPawnCanTake[2];
U64 support_mask[2][64];
int mg_pst_data[2][6][64];
int eg_pst_data[2][6][64];
int mg[2];
int eg[2];

sEvalHashEntry EvalTT[EVAL_HASH_SIZE];

void ClearEvalHash(void) {

  for (int e = 0; e < EVAL_HASH_SIZE; e++) {
    EvalTT[e].key = 0;
    EvalTT[e].score = 0;
  }
}

void InitEval(void) {

  for (int sq = 0; sq < 64; sq++) {
    for (int sd = 0; sd < 2; sd++) {
      mg_pst_data[sd][P][REL_SQ(sq, sd)] = pstPawnMg[sq] + tp_value[P];
      eg_pst_data[sd][P][REL_SQ(sq, sd)] = pstPawnEg[sq] + tp_value[P];
      mg_pst_data[sd][N][REL_SQ(sq, sd)] = pstKnightMg[sq] + tp_value[N];
      eg_pst_data[sd][N][REL_SQ(sq, sd)] = pstKnightEg[sq] + tp_value[N];
      mg_pst_data[sd][B][REL_SQ(sq, sd)] = pstBishopMg[sq] + tp_value[B];
      eg_pst_data[sd][B][REL_SQ(sq, sd)] = pstBishopEg[sq] + tp_value[B];
      mg_pst_data[sd][R][REL_SQ(sq, sd)] = pstRookMg[sq] + tp_value[R];
      eg_pst_data[sd][R][REL_SQ(sq, sd)] = tp_value[R]; // no value from the table
      mg_pst_data[sd][Q][REL_SQ(sq, sd)] = pstQueenMg[sq] + tp_value[Q];
      eg_pst_data[sd][Q][REL_SQ(sq, sd)] = pstQueenEg[sq] + tp_value[Q];
      mg_pst_data[sd][K][REL_SQ(sq, sd)] = pstKingMg[sq];
      eg_pst_data[sd][K][REL_SQ(sq, sd)] = pstKingEg[sq];
    }
  }

  // Init adjacent mask (for detecting isolated pawns)

  for (int i = 0; i < 8; i++) {
	  adjacent_mask[i] = 0;
	  if (i > 0) adjacent_mask[i] |= FILE_A_BB << (i - 1);
	  if (i < 7) adjacent_mask[i] |= FILE_A_BB << (i + 1);
  }

  // Init support mask (for detecting weak pawns)

  for (int sq = 0; sq < 64; sq++) {
    support_mask[WC][sq] = ShiftWest(SqBb(sq)) | ShiftEast(SqBb(sq));
    support_mask[WC][sq] |= FillSouth(support_mask[WC][sq]);

    support_mask[BC][sq] = ShiftWest(SqBb(sq)) | ShiftEast(SqBb(sq));
    support_mask[BC][sq] |= FillNorth(support_mask[BC][sq]);
  }
}

int EvaluatePieces(POS *p, int sd) {

  U64 bbPieces, bbMob, bbAtt, bbFile;
  int op, sq, cnt, ksq, att, wood, mob, tmp;

  // Is color OK?

  assert(sd == WC || sd == BC);

  // Init variables

  op = Opp(sd);
  ksq = KingSq(p, op);
  att = 0;
  wood = 0;

  // Init enemy king zone for attack evaluation

  U64 bbZone = k_attacks[ksq];
  if (sd == WC) bbZone |= ShiftSouth(bbZone);
  else          bbZone |= ShiftNorth(bbZone);

  mob = 0;

  // Knight

  bbPieces = PcBb(p, sd, N);
  while (bbPieces) {
    sq = PopFirstBit(&bbPieces);
    
    // Knight mobility

    bbMob = n_attacks[sq] & ~p->cl_bb[sd];
    cnt = PopCnt(bbMob &~bbPawnTakes[op]) - 4;
    Add(sd, 4*cnt, 4*cnt);

    // Knight attacks on enemy king zone

    bbAtt = n_attacks[sq];
    if (bbAtt & bbZone) {
      wood++;
      att += 5 * PopCnt(bbAtt & bbZone);
    }

    // Knight outpost

    tmp = pstKnightOutpost[REL_SQ(sq, sd)];
    if (SqBb(sq) & ~bbPawnCanTake[op]) 
      Add(sd, tmp, tmp);
  }

  // Bishop

  bbPieces = PcBb(p, sd, B);
  while (bbPieces) {
    sq = PopFirstBit(&bbPieces);
  
    // Bishop mobility

    bbMob = BAttacks(OccBb(p), sq);
    cnt = PopCnt(bbMob &~bbPawnTakes[op]) - 7;
    Add(sd, 5 * cnt, 5 * cnt);

    // Bishop attacks on enemy king zone

    bbAtt = BAttacks(OccBb(p) ^ PcBb(p,sd, Q) , sq);
    if (bbAtt & bbZone) {
      wood++;
      att += 4 * PopCnt(bbAtt & bbZone);
    }

    // Bishop outpost

    tmp = pstBishopOutpost[REL_SQ(sq, sd)];
    if (SqBb(sq) & ~bbPawnCanTake[op])
      Add(sd, tmp, tmp);
  }

  // Rook

  bbPieces = PcBb(p, sd, R);
  while (bbPieces) {
    sq = PopFirstBit(&bbPieces);
  
    // Rook mobility

    bbMob = RAttacks(OccBb(p), sq);
    cnt = PopCnt(bbMob) - 7;
    Add(sd, 2 * cnt, 4 * cnt);

    // Rook attacks on enemy king zone

    bbAtt = RAttacks(OccBb(p) ^ PcBb(p, sd, Q) ^ PcBb(p, sd, R), sq);
    if (bbAtt & bbZone) {
      wood++;
      att += 8 * PopCnt(bbAtt & bbZone);
    }

    // Rook on (half) open file

    bbFile = FillNorth(SqBb(sq)) | FillSouth(SqBb(sq));
    if (!(bbFile & PcBb(p, sd, P))) {
      if (!(bbFile & PcBb(p, op, P))) Add(sd, 10, 10);
      else                            Add(sd,  5,  5);
    }

    // Rook on 7th rank attacking pawns or cutting off enemy king

    if (SqBb(sq) & bbRelRank[sd][RANK_7]) {
      if (PcBb(p, op, P) & bbRelRank[sd][RANK_7]
      ||  PcBb(p, op, K) & bbRelRank[sd][RANK_8]) {
          Add(sd, 16, 32);
      }
    }
  }

  // Queen

  bbPieces = PcBb(p, sd, Q);
  while (bbPieces) {
    sq = PopFirstBit(&bbPieces);

    // Queen mobility

    bbMob = QAttacks(OccBb(p), sq);
    cnt = PopCnt(bbMob) - 14;
    Add(sd, 1 * cnt, 2 * cnt);

    // Queen attacks on enemy king zone
   
    bbAtt  = BAttacks(OccBb(p) ^ PcBb(p, sd, B) ^ PcBb(p, sd, Q), sq);
    bbAtt |= RAttacks(OccBb(p) ^ PcBb(p, sd, B) ^ PcBb(p, sd, Q), sq);
    if (bbAtt & bbZone) {
      wood++;
      att += 16 * PopCnt(bbAtt & bbZone);
    }
  }

  // Score king attacks if own queen is present

  if (wood > 1 && p->cnt[sd][Q]) mob += att * (wood-1);
  
  return mob;
}

void EvaluatePawns(POS *p, int sd) {

  U64 bbPieces, bbSpan;
  int sq;

  // Is color OK?

  assert(sd == WC || sd == BC);

  // Loop through the pawns, evaluating each one

  bbPieces = PcBb(p, sd, P);
  while (bbPieces) {
    sq = PopFirstBit(&bbPieces);

  // Doubled pawn

  bbSpan = FillNorth(ShiftNorth(SqBb(sq)));
  if (bbSpan & PcBb(p, sd, P))
	  Add(sd, -10, -20);

  // Passed pawn

  if (!(passed_mask[sd][sq] & PcBb(p, Opp(sd), P)))
    Add(sd, passed_bonus_mg[sd][Rank(sq)], passed_bonus_eg[sd][Rank(sq)]);

  // Isolated pawn

  if (!(adjacent_mask[File(sq)] & PcBb(p, sd, P)))
    Add(sd, -20, -20);

  // Backward pawn

  else if ((support_mask[sd][sq] & PcBb(p, sd, P)) == 0)
    Add(sd, -16, -8);
  }
}

void EvaluateKing(POS *p, int sd) {

  const int startSq[2] = { E1, E8 };
  const int qCastle[2] = { B1, B8 };
  const int kCastle[2] = { G1, G8 };

  U64 bbKingFile, bbNextFile;
  int result = 0;
  int sq = KingSq(p, sd);

  // Normalize king square for pawn shield evaluation,
  // to discourage shuffling the king between g1 and h1.

  if (SqBb(sq) & bbKSCastle[sd]) sq = kCastle[sd];
  if (SqBb(sq) & bbQSCastle[sd]) sq = qCastle[sd];

  // Evaluate shielding and storming pawns on each file.

  bbKingFile = FillNorth(SqBb(sq)) | FillSouth(SqBb(sq));
  result += EvalKingFile(p, sd, bbKingFile);

  bbNextFile = ShiftEast(bbKingFile);
  if (bbNextFile) result += EvalKingFile(p, sd, bbNextFile);

  bbNextFile = ShiftWest(bbKingFile);
  if (bbNextFile) result += EvalKingFile(p, sd, bbNextFile);

  mg[sd] += result;
}

int EvalKingFile(POS * p, int sd, U64 bbFile) {

  int shelter = EvalFileShelter(bbFile & PcBb(p, sd, P), sd);
  int storm   = EvalFileStorm  (bbFile & PcBb(p, Opp(sd), P), sd);
  if (bbFile & bbCentralFile) return (shelter / 2) + storm;
  else return shelter + storm;
}

int EvalFileShelter(U64 bbOwnPawns, int sd) {

  if (!bbOwnPawns) return -36;
  if (bbOwnPawns & bbRelRank[sd][RANK_2]) return    2;
  if (bbOwnPawns & bbRelRank[sd][RANK_3]) return  -11;
  if (bbOwnPawns & bbRelRank[sd][RANK_4]) return  -20;
  if (bbOwnPawns & bbRelRank[sd][RANK_5]) return  -27;
  if (bbOwnPawns & bbRelRank[sd][RANK_6]) return  -32;
  if (bbOwnPawns & bbRelRank[sd][RANK_7]) return  -35;
  return 0;
}

int EvalFileStorm(U64 bbOppPawns, int sd) {

  if (!bbOppPawns) return -16;
  if (bbOppPawns & bbRelRank[sd][RANK_3]) return -32;
  if (bbOppPawns & bbRelRank[sd][RANK_4]) return -16;
  if (bbOppPawns & bbRelRank[sd][RANK_5]) return -8;
  return 0;
}
 
int Evaluate(POS *p) {

  // Try to retrieve score from eval hashtable

  int addr = p->hash_key % EVAL_HASH_SIZE;
  if (EvalTT[addr].key == p->hash_key) {
    int hashScore = EvalTT[addr].score;
    return p->side == WC ? hashScore : -hashScore;
  }

  // Init eval with incrementally updated stuff

  int score = 0;
  mg[WC] = p->mg_pst[WC];
  mg[BC] = p->mg_pst[BC];
  eg[WC] = p->eg_pst[WC];
  eg[BC] = p->eg_pst[BC];

  // Calculate variables used during evaluation

  bbPawnTakes[WC] = GetWPControl(PcBb(p, WC, P));
  bbPawnTakes[BC] = GetBPControl(PcBb(p, BC, P));
  bbPawnCanTake[WC] = FillNorth(bbPawnTakes[WC]);
  bbPawnCanTake[BC] = FillSouth(bbPawnTakes[BC]);

  // Tempo bonus

  mg[p->side] += 10;
  eg[p->side] += 5;

  // Bishop pair

  if (PopCnt(PcBb(p, WC, B)) > 1) score += 50;
  if (PopCnt(PcBb(p, BC, B)) > 1) score -= 50;

  // Evaluate pieces and pawns

  score += EvaluatePieces(p, WC) - EvaluatePieces(p, BC);
  EvaluatePawns(p, WC); 
  EvaluatePawns(p, BC);
  EvaluateKing(p, WC);
  EvaluateKing(p, BC);
  
  // Merge mg/eg scores

  int mg_phase = Min(max_phase, p->phase);
  int eg_phase = max_phase - mg_phase;
  int mg_score = mg[WC] - mg[BC];
  int eg_score = eg[WC] - eg[BC];
  score += (((mg_score * mg_phase) + (eg_score * eg_phase)) / max_phase);

  // Make sure eval doesn't exceed mate score

  if (score < -MAX_EVAL)
    score = -MAX_EVAL;
  else if (score > MAX_EVAL)
    score = MAX_EVAL;

  // Save eval score in the evaluation hash table

  EvalTT[addr].key = p->hash_key;
  EvalTT[addr].score = score;

  // Return score relative to the side to move

  return p->side == WC ? score : -score;
}

void Add(int sd, int mg_bonus, int eg_bonus) {

  mg[sd] += mg_bonus;
  eg[sd] += eg_bonus;
}