/***************************************************************************
 *   Copyright (C) 2006 by Jan Mayer                                       *
 *   jan.mayer@mathematik.uni-karlsruhe.de                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#pragma once

#ifndef PARAMETERS_H
#define PARAMETERS_H


namespace iluplusplus {


class precond_parameter
  {
       public:
          virtual ~precond_parameter(){};
          virtual std::string convert_to_string() const = 0;
  };

//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: ILUC Preconditioner (Saad):                                                                         //
//                                                                                                                       //
//***********************************************************************************************************************//

class ILUC_precond_parameter : public precond_parameter
  {
      private:
         Integer fill_in;
         Real threshold;
      public:
         ILUC_precond_parameter();
         ILUC_precond_parameter(Integer fi, Real th);
         ILUC_precond_parameter(const ILUC_precond_parameter& p);
         ILUC_precond_parameter& operator =(const ILUC_precond_parameter& p);
         Integer get_fill_in() const;
         Real get_threshold() const;
         virtual std::string convert_to_string() const;
         void set(Integer fi, Real th);
         void set_threshold(Real th);
  };

//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: ILUT Preconditioner (Saad):                                                                        //
//                                                                                                                       //
//***********************************************************************************************************************//

class ILUT_precond_parameter : public precond_parameter
  {
      protected:
         Integer fill_in;
         Real threshold;
      public:
         ILUT_precond_parameter();
         ILUT_precond_parameter(Integer fi, Real th);
         ILUT_precond_parameter(const ILUT_precond_parameter& p);
         ILUT_precond_parameter& operator =(const ILUT_precond_parameter& p);
         Integer get_fill_in() const;
         Real get_threshold() const;
         virtual std::string convert_to_string() const;
         void set(Integer fi, Real th);
         void set_threshold(Real th);
  };

class ILUTP_precond_parameter : public precond_parameter
  {
      protected:
         Integer fill_in;
         Real threshold;
         Real perm_tol;
         Integer row_pos;
      public:
         ILUTP_precond_parameter();
         ILUTP_precond_parameter(Integer fi, Real th, Real pt, Integer rp);
         ILUTP_precond_parameter(const ILUTP_precond_parameter& p);
         ILUTP_precond_parameter& operator =(const ILUTP_precond_parameter& p);
         Integer get_fill_in() const;
         Integer get_row_pos() const;
         Real get_threshold() const;
         Real get_perm_tol() const;
         virtual std::string convert_to_string() const;
         void set(Integer fi, Real th, Real pt, Integer rp);
         void set_threshold(Real th);
  };


//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: ILUCP Preconditioner:                                                                              //
//                                                                                                                       //
//***********************************************************************************************************************//

class ILUCP_precond_parameter : public precond_parameter
  {
      protected:
         Integer fill_in;
         Real threshold;
         Real perm_tol;
         Integer row_pos;
      public:
         ILUCP_precond_parameter();
         ILUCP_precond_parameter(Integer fi, Real th, Real pt, Integer rp) ; // default rp = -1
         ILUCP_precond_parameter(const ILUCP_precond_parameter& p);
         ILUCP_precond_parameter& operator =(const ILUCP_precond_parameter& p);
         Integer get_fill_in() const ;
         Real get_threshold() const;
         Real get_perm_tol() const;
         Integer get_row_pos() const;
         virtual std::string convert_to_string() const;
         void set(Integer fi, Real th, Real pt, Integer rp);
         void set_row_pos(Integer rp);
         void set_threshold(Real th);
         void set_perm_tol(Real pt);
  };



//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: ILUCDP Preconditioner:                                                                             //
//                                                                                                                       //
//***********************************************************************************************************************//

class ILUCDP_precond_parameter : public precond_parameter
  {
      protected:
         Integer fill_in;
         Real threshold;
         Real perm_tol;
         Integer begin_perm_row;
      public:
         ILUCDP_precond_parameter();
         ILUCDP_precond_parameter(Integer fi, Real th, Real pt, Integer bpr);  // default bpr = 1
         ILUCDP_precond_parameter(const ILUCDP_precond_parameter& p);
         ILUCDP_precond_parameter& operator =(const ILUCDP_precond_parameter& p);
         Integer get_fill_in() const;
         Real get_threshold() const;
         Real get_perm_tol() const;
         Integer get_begin_perm_row() const;
         virtual std::string convert_to_string() const;
         void set(Integer fi, Real th, Real pt, Integer bpr);  // default bpr = 1
         void set_threshold(Real th);
         void set_perm_tol(Real pt);
         void set_begin_perm_row(Integer pbr);
  };

//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: ILUTPD Preconditioner (Saad) and subsequent dropping:                                              //
//                                                                                                                       //
//***********************************************************************************************************************//

class ILUTPD_precond_parameter : public precond_parameter
  {
      private:
         Integer working_fill_in;
         Real working_threshold;
         Integer fill_in;
         Real threshold;
      public:
         ILUTPD_precond_parameter();
         ILUTPD_precond_parameter(Integer wfi, Real wth, Integer fi, Real th);
         ILUTPD_precond_parameter(const ILUTPD_precond_parameter& p);
         ILUTPD_precond_parameter& operator =(const ILUTPD_precond_parameter& p);
         Integer get_working_fill_in() const;
         Real get_working_threshold() const;
         Integer get_fill_in() const;
         Real get_threshold() const;
         virtual std::string convert_to_string() const;
         void set(Integer wfi, Real wth, Integer fi, Real th);
  };


//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: iluplusplus_precond_parameter                                                                      //
//                                                                                                                       //
//***********************************************************************************************************************//

class iluplusplus_precond_parameter : public precond_parameter
  {
      protected:
         Integer                  fill_in;
         Real                     threshold;
         Real                     perm_tol;               // pivot tolerance. 0 = pivot always; 500 = pivot to avoid zero pivot; 1000 = never pivot
         std::string              GLOBAL_COMMENT;
         Integer                  PRECON_PARAMETER;       // number of preconditioner. -1: use PARDISO as a direct solver.
         preprocessing_sequence   PREPRPOCESSING;
         Real                     PQ_THRESHOLD;           // threshold for PQ-Ordering. If larger, less rows are selected resulting in more levels.
         Integer                  PQ_ALGORITHM;           // indicates which PQ algorithm will be used.
                                                          //  0: standard greedy PC
                                                          //  1: dynamic averaging PQ
                                                          //  3: symmetrized dynamic averaging PQ for I-matrices
         Integer                  MAX_LEVELS;             // maximum number of levels used by preconditioner. (must be <= MEMORY_RESERVED_LEVELS !!!)
         bool                     MAX_FILLIN_IS_INF;      // if true, do not restrict the number of fill-in elements by number per row/colums (only by threshold)
         Integer                  MEMORY_MAX_LEVELS;
         bool                     BEGIN_TOTAL_PIV;        // true: switch to perm_tol = 0.0 (pivot always), when TOTAL_PIV indicates
         Integer                  TOTAL_PIV;              // if(BEGIN_TOTAL_PIV): indicates how pivoting always should be started
                                                          //     0 = never
                                                          //     1 = only after row indicated by preprocessing on final level (never if no index returned by preprocessing)
                                                          //     2 = always
         Integer                  MIN_ML_SIZE ;           // multilevel keeps adding levels until matrix size is smaller than MIN_ML_SIZE
         bool                     USE_FINAL_THRESHOLD ;   // use different threshold for last level (i.e. for size < MIN_ML_SIZE)
         Real                     FINAL_THRESHOLD ;       // threshold shift for final level; default: keep all elements. Requires USE_FINAL_THRESHOLD == true
         Real                     VARY_THRESHOLD_FACTOR;  // factor to vary threshold by; default: same threshold for all levels
         Real                     THRESHOLD_SHIFT_SCHUR;  // additive shift for threshold for Schur Complement; Schur Complement is calculated with threshold+THRESHOLD_SHIFT_SCHUR
         Integer                  PERMUTE_ROWS;           // indicates which rows should be permuted:
                                                          //     0 = never
                                                          //     1 = permute only the final rows unaffected by resorting on final level (same as 0 if !EXTERNAL_FINAL_ROW)
                                                          //     2 = permute only in a reordering block (same as 3 if not EXTERNAL_FINAL_ROW)
                                                          //     3 = permit permute in entire matrix
         bool                     EXTERNAL_FINAL_ROW;     // if(EXTERNAL_FINAL_ROW) final row is passed as an argument and usually comes from an ordering, i.e. from PQ sorting
                                                          // else:       use MIN_ELIM_FACTOR or an intrinsic criterion, e.g. too much fill-in, pivot too small,...
         Real                     MIN_ELIM_FACTOR;        // if (!EXTERNAL_FINAL_ROW): minimum number of rows that must be eliminated before moving to next level
         Real                     EXT_MIN_ELIM_FACTOR;    // if ( EXTERNAL_FINAL_ROW): minimum fraction of number of rows that must be eliminated before moving to next level
         bool                     REQUIRE_ZERO_SCHUR;     // stops factorization prematurely and requires a zero Schur Complement
         Integer                  REQ_ZERO_SCHUR_SIZE;    // minimum dimension of zero Schur Complement that is required.
         Integer                  FINAL_ROW_CRIT;         // determines preconditioner moves to next level:
                                                          // if (!EXTERNAL_FINAL_ROW): Criterion for moving to next level:
                                                          //    -4 = move if every weighted norm of every non-eliminated row of L (weight corresponds to norm of row of U*pivot) is larger than MOVE_LEVEL_THRESHOLD
                                                          //    -3 = move if every weighted norm of every non-eliminated row of L (weight corresponds to norm of row of U) is larger than MOVE_LEVEL_THRESHOLD
                                                          //    -2 = move if every norm of every non-eliminated row of L is larger than MOVE_LEVEL_THRESHOLD
                                                          //    -1 = move if every non-eliminated row of L has more MOVE_LEVEL_FACTOR*nnz(A)/n(A)
                                                          //    the following are deprecated, but functional
                                                          //     0 = move if every non-eliminated row of L has more 0.5*nnz(A)/n(A)
                                                          //     1 = move if every non-eliminated row of L has more nnz(A)/n(A)
                                                          //     2 = move if every non-eliminated row of L has more 2*nnz(A)/n(A)
                                                          //     3 = move if every non-eliminated row of L has more 4*nnz(A)/n(A)
                                                          //     4 = move if every non-eliminated row of L has more 6*nnz(A)/n(A)
                                                          //     5 = move if every non-eliminated row of L has more than 10 elements
                                                          //     6 = move if every non-eliminated row of L has more than 1.5*nnz(A)/n(A)
                                                          //     7 = use ROW_U_MAX
                                                          //     8 = move if every non-eliminated row of L has more than 3*nnz(A)/n(A)
                                                          //     9 = move if every non-eliminated row of L has more than 1.3*nnz(A)/n(A)
                                                          //     deprecated and no longer functional:
                                                          //    10 = terminate level if half the rows have been eliminated
                                                          //    not deprecated
                                                          //    11 = do not use any of the criteria above (if you may want to terminate by pivot size, set SMALL_PIVOT_TERMINATES = true)
         bool                     SMALL_PIVOT_TERMINATES; // if true, level is terminated, whenever fabs(pivot) < MIN_PIVOT.
         Real                     MIN_PIVOT;              // if (SMALL_PIVOT_TERMINATES) move level if fabs(pivot) is less than this threshold
         bool                     USE_THRES_ZERO_SCHUR;   // if (USE_THRES_ZERO_SCHUR) check if normF(Schur Complement) < THRESHOLD_ZERO_SCHUR and dimension<= < MIN_SIZE_ZERO_SCHUR
                                                          // and if this is the case, factor it as LDU with L=U=I, D=0 and use for D^{-1} = 0 (Drazin Inverse)
                                                          // NOTE: this only makes sense if SMALL_PIVOT_TERMINATES == true.
         Real                     THRESHOLD_ZERO_SCHUR;   // see above.
         Integer                  MIN_SIZE_ZERO_SCHUR;
         Real                     ROW_U_MAX;              // if(!EXTERNAL_FINAL_ROW && FINAL_ROW_CRIT==7): move to next level, if norm of row of U > ROW_U_MAX.
         Real                     MOVE_LEVEL_FACTOR;      // used only if FINAL_ROW_CRIT==-1
         Real                     MOVE_LEVEL_THRESHOLD;   // used only if FINAL_ROW_CRIT==-2
         bool                     USE_MAX_AS_MOVE;        // used only if FINAL_ROW_CRIT==-2: move level if max of norm is larger than threshold, else use min.
         Real                     MEM_FACTOR;             // approximate maximal fill-in for allocating memory
         Integer                  VARIABLE_MEM;           // Memfactor is dependent on level. For increasing levels, memfactor increases.
                                                          //     0 = memfactor is constant
                                                          //     1 = memfactor is multiplied by size_orig/size
                                                          //     2 = memfactor is multiplied by (size_orig/size)^2
         bool                     USE_STANDARD_DROPPING;  // indicates if (relative) standard dropping should be used, i.e weight for column of L w = 1/norm2(w)
         bool                     USE_STANDARD_DROPPING2; // indicates if (absolute) standard dropping should be used, i.e weight for column of L w = 1
         bool                     USE_INVERSE_DROPPING;   // indicates if inverse-based dropping should be be used, i.e. weight for column k of L is ||e^k*L^{-1}||
         bool                     USE_WEIGHTED_DROPPING;  // indicates if weighted dropping should be be used, i.e row of U is scaled with norm of row of L and column of L by norm of column of U: estimates inverse error.
         bool                     USE_WEIGHTED_DROPPING2; // indicates if weighted dropping should be be used, i.e row of U is scaled with norm of row of L and column of L by norm of column of U: estimates inverse error.
                                                          // further scaling: next column of L is scaled with row sums of L already calculated.
         bool                     USE_ERR_PROP_DROPPING;  // indicates if dropping based on reducing error propagation in calculations should be used, i.e. a row of U is scaled by a column of L and vice versa.
         bool                     USE_ERR_PROP_DROPPING2; // indicates if dropping based on reducing error propagation2 in calculations should be used, i.e. a row of U is scaled by a column of L multiplied with diagonal element and vice versa.
         bool                     USE_PIVOT_DROPPING;     // indicates if dropping based on inverse of pivot is used
         Real                     INIT_WEIGHTS_LU;        // for weighted dropping: set 1.0 for diagonal element, 0.0 to ignore diagonal element in weighing
         Integer                  DROP_TYPE_L;            //
         Integer                  DROP_TYPE_U;            // indicates which dropping is used:
                                                          // 0: normal dropping with a single weight for all elements of vector, drop if z_i*w is too small
                                                          // 1: positional dropping. All elements are weighted based on distance to diagonal using TABLE_POSITIONAL_WEIGHTS. (should not be used if row/columns are permuted)
                                                          // 2: all elements are weighted using fixed weight and a weight based on index. Only used if USE_WEIGHTED_DROPPING2 = true;
                                                          // 3: banded dropping. For L and U: only elements within a band of width -ln(tau) are kept. (not compatible with pivoting)
                                                          // 4: positional dropping using natural bandwidth.
         Real                     BANDWIDTH_MULTIPLIER;   // see below
         Integer                  BANDWIDTH_OFFSET;       // maximal bandwidth = BANDWIDTH_OFFSET + BANDWIDTH_MULTIPLIER*n
         Integer                  SIZE_TABLE_POS_WEIGHTS; // size of table used -1
         Real_Array               TABLE_POSITIONAL_WEIGHTS;
         Integer                  WEIGHT_TABLE_TYPE;      // type of table used.
         bool                     SCALE_WEIGHT_INVDIAG;   // indicates if dropping threshold is scaled by inverse of diagonal element, i.e. final weight is scaled by 1/|d(i,i)|.
         bool                     SCALE_WGT_MAXINVDIAG;   // indicates if dropping threshold is scaled by maximal inverse of diagonal element, i.e. final weight is scaled by msx 1/|d(i,i)|.
         Real                     WEIGHT_STANDARD_DROP;
         Real                     WEIGHT_STANDARD_DROP2;
         Real                     WEIGHT_INVERSE_DROP;
         Real                     WEIGHT_WEIGHTED_DROP;
         Real                     WEIGHT_ERR_PROP_DROP;
         Real                     WEIGHT_ERR_PROP_DROP2;
         Real                     WEIGHT_PIVOT_DROP;
         Integer                  COMBINE_FACTOR;        // combines various weights as indicated in function below.
         Real                     NEUTRAL_ELEMENT;
         Real                     MIN_WEIGHT;            // only for COMBINE_FACTOR == 3
         bool                     WEIGHTED_DROPPING;     // given a weight w: drop an element z_i of z if |z_i|*w < tau
         bool                     SUM_DROPPING;          // given a weight w: drop the smallest elements z_i of z as long as sum_i |z_i|*w < tau
         bool                     USE_POS_COMPRESS;      // drop elements after factorisation based on TABLE_POSITIONAL_WEIGHTS and absolute value, else just on absolute value;
         Real                     POST_FACT_THRESHOLD;   // threshold for dropping after factorisation.
         Integer                  SCHUR_COMPLEMENT;      // indicates which Schur Complement should be used. 0 = standard; 1 = improved.
         //## new parameter demands change here
      public:
         iluplusplus_precond_parameter();
         ~iluplusplus_precond_parameter();
         iluplusplus_precond_parameter(const iluplusplus_precond_parameter& p);
         iluplusplus_precond_parameter& operator =(const iluplusplus_precond_parameter& p);
         void default_parameters();                      // sets default parameters
         void make_table();                              // sets up table of dropping weights
         virtual std::string convert_to_string() const;
         void set(Integer fi, Real th, Real pt);
         void print() const;
         Real combine(Real x, Real y) const; // routine for combining weights
         void init(const preprocessing_sequence& L, Integer precon_parameter, std::string global_comment);
         void default_configuration(Integer configuration);
         std::string filename() const;
         std::string precondname() const;
         std::string short_string() const;
         std::string filename(std::string matrix_name) const;
         // inline functions
         Integer                  get_fill_in() const;
         Real                     get_threshold() const;
         Real                     get_perm_tol() const;
         std::string              get_GLOBAL_COMMENT() const;
         Integer                  get_PRECON_PARAMETER() const;
         preprocessing_sequence   get_PREPROCESSING() const;
         Real                     get_PQ_THRESHOLD() const;
         Integer                  get_PQ_ALGORITHM() const;
         Integer                  get_MAX_LEVELS() const;
         bool                     get_MAX_FILLIN_IS_INF() const;
         Integer                  get_MEMORY_MAX_LEVELS() const;
         bool                     get_BEGIN_TOTAL_PIV() const;
         Integer                  get_TOTAL_PIV() const;
         Integer                  get_MIN_ML_SIZE() const;
         bool                     get_USE_FINAL_THRESHOLD() const;
         Real                     get_FINAL_THRESHOLD() const;
         Real                     get_VARY_THRESHOLD_FACTOR() const;
         Real                     get_THRESHOLD_SHIFT_SCHUR() const;
         Integer                  get_PERMUTE_ROWS() const;
         bool                     get_EXTERNAL_FINAL_ROW() const;
         Real                     get_MIN_ELIM_FACTOR() const;
         Real                     get_EXT_MIN_ELIM_FACTOR() const;
         bool                     get_REQUIRE_ZERO_SCHUR() const;
         Integer                  get_REQ_ZERO_SCHUR_SIZE() const;
         Integer                  get_FINAL_ROW_CRIT() const;
         bool                     get_SMALL_PIVOT_TERMINATES() const;
         Real                     get_MIN_PIVOT() const;
         bool                     get_USE_THRES_ZERO_SCHUR() const;
         Real                     get_THRESHOLD_ZERO_SCHUR() const;
         Integer                  get_MIN_SIZE_ZERO_SCHUR() const;
         Real                     get_ROW_U_MAX() const;
         Real                     get_MOVE_LEVEL_FACTOR() const;
         Real                     get_MOVE_LEVEL_THRESHOLD() const;
         bool                     get_USE_MAX_AS_MOVE() const;
         Real                     get_MEM_FACTOR() const;
         Integer                  get_VARIABLE_MEM() const;
         bool                     get_USE_STANDARD_DROPPING() const;
         bool                     get_USE_STANDARD_DROPPING2() const;
         bool                     get_USE_INVERSE_DROPPING() const;
         bool                     get_USE_WEIGHTED_DROPPING() const;
         bool                     get_USE_WEIGHTED_DROPPING2() const;
         bool                     get_USE_ERR_PROP_DROPPING() const;
         bool                     get_USE_ERR_PROP_DROPPING2() const;
         bool                     get_USE_PIVOT_DROPPING() const;
         Real                     get_INIT_WEIGHTS_LU() const;
         Integer                  get_DROP_TYPE_L() const;
         Integer                  get_DROP_TYPE_U() const;
         Real                     get_BANDWIDTH_MULTIPLIER() const;
         Integer                  get_BANDWIDTH_OFFSET() const;
         Integer                  get_SIZE_TABLE_POS_WEIGHTS() const;
         Real                     get_TABLE_POSITIONAL_WEIGHTS(Integer k) const;
         Integer                  get_WEIGHT_TABLE_TYPE() const;
         bool                     get_SCALE_WEIGHT_INVDIAG() const;
         bool                     get_SCALE_WGT_MAXINVDIAG() const;
         Real                     get_WEIGHT_STANDARD_DROP() const;
         Real                     get_WEIGHT_STANDARD_DROP2() const;
         Real                     get_WEIGHT_INVERSE_DROP() const;
         Real                     get_WEIGHT_WEIGHTED_DROP() const;
         Real                     get_WEIGHT_ERR_PROP_DROP() const;
         Real                     get_WEIGHT_ERR_PROP_DROP2() const;
         Real                     get_WEIGHT_PIVOT_DROP() const;
         Integer                  get_COMBINE_FACTOR() const;
         Real                     get_NEUTRAL_ELEMENT() const;
         Real                     get_MIN_WEIGHT() const;
         bool                     get_WEIGHTED_DROPPING() const;
         bool                     get_SUM_DROPPING() const;
         bool                     get_USE_POS_COMPRESS() const;
         Real                     get_POST_FACT_THRESHOLD() const; 
         Integer                  get_SCHUR_COMPLEMENT() const;
         //## new parameter demands change here
         void                     set_fill_in(Integer x);
         void                     set_threshold(Real x);
         void                     set_perm_tol(Real x);
         void                     set_GLOBAL_COMMENT(std::string x);
         void                     set_PRECON_PARAMETER(Integer x);
         void                     set_PREPROCESSING(preprocessing_sequence x);
         void                     set_PQ_THRESHOLD(Real x);
         void                     set_PQ_ALGORITHM(Integer x);
         void                     set_MAX_LEVELS(Integer x);
         void                     set_MAX_FILLIN_IS_INF(bool x);
         void                     set_MEMORY_MAX_LEVELS(Integer x);
         void                     set_BEGIN_TOTAL_PIV(bool x);
         void                     set_TOTAL_PIV(Integer x);
         void                     set_MIN_ML_SIZE(Integer x);
         void                     set_USE_FINAL_THRESHOLD(bool x);
         void                     set_FINAL_THRESHOLD(Real x);
         void                     set_VARY_THRESHOLD_FACTOR(Real x);
         void                     set_THRESHOLD_SHIFT_SCHUR(Real x);
         void                     set_PERMUTE_ROWS(Integer x);
         void                     set_EXTERNAL_FINAL_ROW(bool x);
         void                     set_MIN_ELIM_FACTOR(Real x);
         void                     set_EXT_MIN_ELIM_FACTOR(Real x);
         void                     set_REQUIRE_ZERO_SCHUR(bool x);
         void                     set_REQ_ZERO_SCHUR_SIZE(Integer x);
         void                     set_FINAL_ROW_CRIT(Integer x);
         void                     set_SMALL_PIVOT_TERMINATES(bool x);
         void                     set_MIN_PIVOT(Real x);
         void                     set_USE_THRES_ZERO_SCHUR(bool x);
         void                     set_THRESHOLD_ZERO_SCHUR(Real x);
         void                     set_MIN_SIZE_ZERO_SCHUR(Integer x);
         void                     set_ROW_U_MAX(Real x);
         void                     set_MOVE_LEVEL_FACTOR(Real x);
         void                     set_MOVE_LEVEL_THRESHOLD(Real x);
         void                     set_USE_MAX_AS_MOVE(bool x);
         void                     set_MEM_FACTOR(Real x);
         void                     set_VARIABLE_MEM(Integer x);
         void                     set_USE_STANDARD_DROPPING (bool x);
         void                     set_USE_STANDARD_DROPPING2 (bool x);
         void                     set_USE_INVERSE_DROPPING (bool x);
         void                     set_USE_WEIGHTED_DROPPING (bool x);
         void                     set_USE_WEIGHTED_DROPPING2 (bool x);
         void                     set_USE_ERR_PROP_DROPPING (bool x);
         void                     set_USE_ERR_PROP_DROPPING2 (bool x);
         void                     set_USE_PIVOT_DROPPING(bool x);
         void                     set_INIT_WEIGHTS_LU (Real x);
         void                     set_DROP_TYPE_L (Integer x);
         void                     set_DROP_TYPE_U (Integer x);
         void                     set_BANDWIDTH_MULTIPLIER (Real x);
         void                     set_BANDWIDTH_OFFSET (Integer x);
         void                     set_SIZE_TABLE_POS_WEIGHTS (Integer x);
         void                     set_WEIGHT_TABLE_TYPE (Integer x);
         void                     set_SCALE_WEIGHT_INVDIAG (bool x);
         void                     set_SCALE_WGT_MAXINVDIAG (bool x);
         void                     set_WEIGHT_STANDARD_DROP (Real x);
         void                     set_WEIGHT_STANDARD_DROP2 (Real x);
         void                     set_WEIGHT_INVERSE_DROP (Real x);
         void                     set_WEIGHT_WEIGHTED_DROP (Real x);
         void                     set_WEIGHT_ERR_PROP_DROP (Real x);
         void                     set_WEIGHT_ERR_PROP_DROP2 (Real x);
         void                     set_WEIGHT_PIVOT_DROP (Real x);
         void                     set_COMBINE_FACTOR (Integer x);
         void                     set_NEUTRAL_ELEMENT (Real x);
         void                     set_MIN_WEIGHT (Real x);
         void                     set_WEIGHTED_DROPPING (bool x);
         void                     set_SUM_DROPPING (bool x);
         void                     set_USE_POS_COMPRESS (bool x);
         void                     set_POST_FACT_THRESHOLD (Real x);
         void                     set_SCHUR_COMPLEMENT(Integer x);
         //## new parameter demands change here
         void use_only_standard_dropping1();
         void use_only_standard_dropping2();
         void use_only_inverse_dropping();
         void use_only_weighted_dropping1();
         void use_only_weighted_dropping2();
         void use_only_error_propagation_dropping1();
         void use_only_error_propagation_dropping2();
         void use_only_pivot_dropping();
  };  // end declaration iluplusplus_precond_parameter


} // end namespace iluplusplus

#endif
