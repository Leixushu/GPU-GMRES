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

#ifndef PRECONDITIONER_H
#define PRECONDITIONER_H

// flags: INFO: more info on levels for Multilevel Preconditioner

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>

#include<vector>


#include "declarations.h"
#include "sparse.h"

//***********************************************************************************************************************//
//                                                                                                                       //
//         The base class preconditioner: declaration                                                                    //
//                                                                                                                       //
//***********************************************************************************************************************//

namespace iluplusplus {

template <class T, class matrix_type, class vector_type> class preconditioner
  {
       protected:
          Real setup_time;
          Real memory_allocated_to_create;
          Real memory_used_to_create;
          Integer pre_image_size;
          Integer image_size;
          bool preconditioner_exists;
          virtual void apply_preconditioner_and_matrix(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &v, vector_type &w) const = 0;
          virtual void apply_preconditioner_and_matrix(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,vector_type &w) const = 0;
          virtual void apply_preconditioner_and_matrix_transposed(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &v, vector_type &w) const = 0;
          virtual void apply_preconditioner_and_matrix_transposed(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,vector_type &w) const = 0;
          virtual void apply_preconditioner_rhs(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &b, vector_type &c) const = 0;
          virtual void apply_preconditioner_rhs(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A, vector_type &c) const = 0;
          virtual void apply_preconditioner_solution(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &y, vector_type &x) const = 0;
          virtual void apply_preconditioner_solution(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,vector_type &x) const = 0;
          virtual void apply_preconditioner_starting_value(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &x, vector_type &y) const = 0;
          virtual void apply_preconditioner_starting_value(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,vector_type &y) const = 0;
       public:
          preconditioner();   // standard constructor
          virtual ~preconditioner();                                  // destructor
          preconditioner(const preconditioner &A);                     // copy-constructor
        // essentials
           // preconditioner operator = (const preconditioner<T, matrix_type, vector_type> &A){pre_image_size=A.pre_image_size; image_size=A.image_size;};
        // preconditioned multiplication with prescribed usage: from left, from right or split preconditioning used as simple, QTQ or QQT preconditioning
          virtual void preconditioned_matrix_vector_multiplication(preconditioner_application1_type PA1, const matrix_type &A, const vector_type &v, vector_type &w) const;
          virtual void preconditioned_matrix_vector_multiplication(preconditioner_application1_type PA1, const matrix_type &A, vector_type &w) const;
        // preconditioned multiplication with prescribed usage: from left, from right or split preconditioning
          virtual void preconditioned_matrix_transposed_vector_multiplication(preconditioner_application1_type PA1, const matrix_type &A, const vector_type &v, vector_type &w) const;
          virtual void preconditioned_matrix_transposed_vector_multiplication(preconditioner_application1_type PA1, const matrix_type &A, vector_type &w) const;
        // appropriate modification of rhs based on preconditioning technique chosen
          virtual void preconditioned_rhs(preconditioner_application1_type PA1, const matrix_type& A, const vector_type &b, vector_type &c) const;
          virtual void preconditioned_rhs(preconditioner_application1_type PA1, const matrix_type& A, vector_type &c) const;
        // appropriate adaption of solution based on preconditioning technique choses
          virtual void adapt_solution(preconditioner_application1_type PA1, const matrix_type& A, const vector_type &y, vector_type &x) const;
          virtual void adapt_solution(preconditioner_application1_type PA1,  const matrix_type& A, vector_type &x) const;
        // appropriate starting value for iteration y based on initial guess of solution x (inverse of adapt_solution).
          virtual void preconditioned_starting_value(preconditioner_application1_type PA1, const matrix_type& A, const vector_type &x, vector_type &y) const;
          virtual void preconditioned_starting_value(preconditioner_application1_type PA1, const matrix_type& A, vector_type &y) const;
        // appropriate residual: r= L*(b-A*x), L being the left part of the preconditioner.
          virtual void preconditioned_residual(preconditioner_application1_type PA1, const matrix_type& A, const vector_type &b, const vector_type &x, vector_type &r) const;
          virtual void apply_preconditioner_only(matrix_usage_type use, const vector_type &x, vector_type &y) const = 0;
          virtual void apply_preconditioner_only(matrix_usage_type use, vector_type &y) const = 0;
          virtual void apply_preconditioner_only(matrix_usage_type use, T* data, Integer dim) const;
          virtual void apply_preconditioner_only(matrix_usage_type use, std::vector<T>& data) const;
          virtual Integer dimension_of_argument_of_multiplication(preconditioner_application1_type PA1, const matrix_type& A) const = 0;
          virtual Integer dimension_of_result_of_multiplication(preconditioner_application1_type PA1, const matrix_type& A) const = 0;
          virtual bool compatibility_check(preconditioner_application1_type PA1, const matrix_type& A, const vector_type& b, const vector_type& x) const = 0;
          virtual bool compatibility_check(preconditioner_application1_type PA1, const matrix_type& A, const vector_type& b) const = 0;
          virtual Integer pre_image_dimension() const;
          virtual Integer image_dimension() const;
          virtual bool exists() const;
          virtual Real memory_used_calculations() const;
          virtual Real memory_allocated_calculations() const;
          virtual Real memory() const;
          virtual std::string special_info() const;
        // info
          virtual Integer total_nnz() const = 0;
          virtual void print_info() const = 0;
          virtual void read_binary(std::string filename) = 0;
          virtual void write_binary(std::string filename) const = 0;
          virtual Real time() const;
          virtual void setup_approximate_inverse(matrix_usage_type mu, matrix_dense<T>& inv) const;
          virtual void setup_preconditioned_matrix(matrix_usage_type mu, preconditioner_application1_type PA, const matrix_type& A, matrix_dense<T>& inv) const;
  };


//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: single_preconditioner,                                                                             //
//                i.e. one operating from only one side on a matrix, either directly or indirectly                       //
//                                                                                                                       //
//***********************************************************************************************************************//


template <class T, class matrix_type, class vector_type>
  class single_preconditioner : public preconditioner  <T, matrix_type, vector_type>
  {
       protected:
          virtual void apply_preconditioner(matrix_usage_type use, const vector_type &v, vector_type &w) const = 0;
          virtual void apply_preconditioner(matrix_usage_type use, vector_type &w) const = 0;
          virtual void unapply_preconditioner(matrix_usage_type use, const vector_type &v, vector_type &w) const = 0;
          virtual void unapply_preconditioner(matrix_usage_type use, vector_type &w) const = 0;
          virtual void apply_preconditioner_and_matrix(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &v, vector_type &w) const;
          virtual void apply_preconditioner_and_matrix(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,vector_type &w) const;
          virtual void apply_preconditioner_and_matrix_transposed(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &v, vector_type &w) const;
          virtual void apply_preconditioner_and_matrix_transposed(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A, vector_type &w) const;
          virtual void apply_preconditioner_rhs(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &b, vector_type &c) const;
          virtual void apply_preconditioner_rhs(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A, vector_type &c) const;
          virtual void apply_preconditioner_solution(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &y, vector_type &x) const;
          virtual void apply_preconditioner_solution(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A, vector_type &x) const;
          virtual void apply_preconditioner_starting_value(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &x, vector_type &y) const;
          virtual void apply_preconditioner_starting_value(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,vector_type &y) const;
       public:
          single_preconditioner();   // standard constructor
          virtual ~single_preconditioner();                                  // destructor
          single_preconditioner(const single_preconditioner &A);             // copy-constructor
          virtual void print_info() const = 0;
          virtual Integer dimension_of_argument_of_multiplication(preconditioner_application1_type PA1, const matrix_type& A) const;
          virtual Integer dimension_of_result_of_multiplication(preconditioner_application1_type PA1, const matrix_type& A) const;
          virtual bool compatibility_check(preconditioner_application1_type PA1, const matrix_type& A, const vector_type& b, const vector_type& x) const;
          virtual bool compatibility_check(preconditioner_application1_type PA1, const matrix_type& A, const vector_type& b) const;
          virtual Integer total_nnz() const = 0; 
          virtual void read_binary(std::string filename) = 0;
          virtual void write_binary(std::string filename) const = 0;
          using preconditioner<T,matrix_type,vector_type>::apply_preconditioner_only;
          virtual void apply_preconditioner_only(matrix_usage_type use,const vector_type &x, vector_type &y) const;
          virtual void apply_preconditioner_only(matrix_usage_type use, vector_type &y) const;
   };



//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: split_preconditioner,                                                                              //
//                i.e. one operating from both sides of a matrix, either directly or indirectly                          //
//                or any preconditioner constisting of two factors.                                                      //
//                                                                                                                       //
//***********************************************************************************************************************//

// For the preconditioner of A, the composition
// Operator_associated_with_Precond_left o A o Operator_associated_with_Precond_right
// should approximate the identity operator.
// i.e. for a direct preconditioner: Precond_left * A * Precond_right = I (approx.), I being the identity matrix,
// for an indirect preconditioner:   Precond_left^{-1} * A * Precond_right^{-1} = I

template <class T, class matrix_type, class vector_type>
  class split_preconditioner : public preconditioner  <T, matrix_type, vector_type>
  {
       protected:
          Integer intermediate_size;
          virtual void apply_preconditioner_left(matrix_usage_type use, const vector_type &v, vector_type &w) const = 0;
          virtual void apply_preconditioner_left(matrix_usage_type use,  vector_type &w) const = 0;
          virtual void apply_preconditioner_right(matrix_usage_type use, const vector_type &v, vector_type &w) const = 0;
          virtual void apply_preconditioner_right(matrix_usage_type use,  vector_type &w) const = 0;
          virtual void unapply_preconditioner_left(matrix_usage_type use, const vector_type &v, vector_type &w) const = 0;
          virtual void unapply_preconditioner_left(matrix_usage_type use, vector_type &w) const = 0;
          virtual void unapply_preconditioner_right(matrix_usage_type use, const vector_type &v, vector_type &w) const = 0;
          virtual void unapply_preconditioner_right(matrix_usage_type use, vector_type &w) const = 0;
          virtual void apply_preconditioner_and_matrix(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &v, vector_type &w) const;
          virtual void apply_preconditioner_and_matrix(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,vector_type &w) const;
          virtual void apply_preconditioner_and_matrix_transposed(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &v, vector_type &w) const;
          virtual void apply_preconditioner_and_matrix_transposed(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A, vector_type &w) const;
          virtual void apply_preconditioner_rhs(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &b, vector_type &c) const;
          virtual void apply_preconditioner_rhs(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,vector_type &c) const;
          virtual void apply_preconditioner_solution(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &y, vector_type &x) const;
          virtual void apply_preconditioner_solution(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A, vector_type &x) const;
          virtual void apply_preconditioner_starting_value(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A,const vector_type &x, vector_type &y) const;
          virtual void apply_preconditioner_starting_value(preconditioner_application1_type PA1, matrix_usage_type use, const matrix_type &A, vector_type &y) const;
       public:
          split_preconditioner();   // standard constructor
          virtual ~split_preconditioner();                               // destructor
          virtual Integer left_nnz() const = 0;
          virtual Integer right_nnz() const = 0;
          virtual Integer total_nnz() const;
          split_preconditioner(const split_preconditioner &A);                     // copy-constructor
          virtual Integer dimension_of_argument_of_multiplication(preconditioner_application1_type PA1,const matrix_type& A) const;
          virtual Integer dimension_of_result_of_multiplication(preconditioner_application1_type PA1, const matrix_type& A) const;
          virtual bool compatibility_check(preconditioner_application1_type PA1, const matrix_type& A, const vector_type& b, const vector_type& x) const;
          virtual bool compatibility_check(preconditioner_application1_type PA1, const matrix_type& A, const vector_type& b) const;
          virtual void print_info() const = 0;
          virtual void read_binary(std::string filename) = 0;
          virtual void write_binary(std::string filename) const = 0;
          using preconditioner<T,matrix_type,vector_type>::apply_preconditioner_only;
          virtual void apply_preconditioner_only(matrix_usage_type use, const vector_type &x, vector_type &y) const;
          virtual void apply_preconditioner_only(matrix_usage_type use,vector_type &y) const;
          virtual void apply_preconditioner_only(preconditioner_application1_type PA1, matrix_usage_type use, const vector_type &x, vector_type &y) const;
          virtual void apply_preconditioner_only(preconditioner_application1_type PA1, matrix_usage_type use, vector_type &y) const;
          virtual void apply_only_left(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void apply_only_left(matrix_usage_type use,  vector_type &w) const;
          virtual void apply_only_right(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void apply_only_right(matrix_usage_type use,  vector_type &w) const;
   };


//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: direct_single_preconditioner                                                                       //
//                                                                                                                       //
//***********************************************************************************************************************//

template <class T, class matrix_type, class vector_type>
  class direct_single_preconditioner : public single_preconditioner <T, matrix_type, vector_type>
  {
      protected:
          matrix_type Precond;    // the preconditioning matrix
          virtual void apply_preconditioner(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void apply_preconditioner(matrix_usage_type use, vector_type &w) const;
          virtual void unapply_preconditioner(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void unapply_preconditioner(matrix_usage_type use,vector_type &w) const;
       public:
          direct_single_preconditioner();
          direct_single_preconditioner(const direct_single_preconditioner &A );
          direct_single_preconditioner& operator =(const direct_single_preconditioner &A);
          virtual ~direct_single_preconditioner();
          virtual void read_binary(std::string filename);
          virtual void write_binary(std::string filename) const;
          virtual void print_info() const;
          virtual matrix_type extract();
          virtual matrix_type& preconditioning_matrix();
          virtual Integer total_nnz() const;
  };


//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: indirect_single_triangular_preconditioner                                                          //
//                                                                                                                       //
//***********************************************************************************************************************//

template <class T, class matrix_type, class vector_type>
  class indirect_single_triangular_preconditioner : public single_preconditioner <T, matrix_type, vector_type>
  {
       protected:
          special_matrix_type matrix_shape;
          virtual void apply_preconditioner(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void apply_preconditioner(matrix_usage_type use, vector_type &w) const;
          virtual void unapply_preconditioner(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void unapply_preconditioner(matrix_usage_type use, vector_type &w) const;
       public:
          indirect_single_triangular_preconditioner();
          virtual~indirect_single_triangular_preconditioner();
          virtual void read_binary(std::string filename) = 0;
          virtual void write_binary(std::string filename) const = 0;
  };


//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: indirect_split_triangular_preconditioner                                                                      //
//                                                                                                                       //
//***********************************************************************************************************************//

template <class T, class matrix_type, class vector_type>
  class indirect_split_triangular_preconditioner : public split_preconditioner <T,matrix_type, vector_type>
  {
       protected:
          matrix_type Precond_left;     // the left preconditioning matrix
          matrix_type Precond_right;    // the right preconditioning matrix
          special_matrix_type left_form;
          special_matrix_type right_form;
          virtual void apply_preconditioner_left(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void apply_preconditioner_left(matrix_usage_type use, vector_type &w) const;
          virtual void apply_preconditioner_right(matrix_usage_type use, const vector_type &v, vector_type &w) const ;
          virtual void apply_preconditioner_right(matrix_usage_type use, const vector_type &w) const;
          virtual void unapply_preconditioner_left(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void unapply_preconditioner_left(matrix_usage_type use, vector_type &w) const;
          virtual void unapply_preconditioner_right(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void unapply_preconditioner_right(matrix_usage_type use, vector_type &w) const;
       public:
          indirect_split_triangular_preconditioner();
          virtual ~indirect_split_triangular_preconditioner();
          virtual matrix_type extract_left_matrix() const;
          virtual matrix_type extract_right_matrix() const;
          virtual Integer left_nnz() const;
          virtual Integer right_nnz() const;
          virtual Integer total_nnz() const;
          virtual matrix_type& left_preconditioning_matrix();
          virtual matrix_type& right_preconditioning_matrix();
          virtual void print_info() const;
          virtual void read_binary(std::string filename) = 0;
          virtual void write_binary(std::string filename) const = 0;
  };


//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: indirect_split_triangular_multilevel_preconditioner                                                //
//                                                                                                                       //
//***********************************************************************************************************************//

template <class T, class matrix_type, class vector_type>
  class indirect_split_triangular_multilevel_preconditioner : public split_preconditioner <T,matrix_type, vector_type>
  {
       protected:
          array<matrix_type> Precond_left;     // the left preconditioning matrices
          array<matrix_type> Precond_right;    // the right preconditioning matrices
          array<vector_type> Precond_middle;
          special_matrix_type left_form;
          special_matrix_type right_form;
          Integer number_levels;
          array<Integer> begin_next_level;
          array<index_list> permutation_rows;
          array<index_list> permutation_columns;
          array<index_list> inverse_permutation_rows;
          array<index_list> inverse_permutation_columns;
          array<vector_type> D_l;  // scaling
          array<vector_type> D_r;  // scaling
          virtual void apply_preconditioner_left(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void apply_preconditioner_left(matrix_usage_type use, vector_type &w) const;
          virtual void apply_preconditioner_right(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void apply_preconditioner_right(matrix_usage_type use, vector_type &w) const;
          virtual void unapply_preconditioner_left(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void unapply_preconditioner_left(matrix_usage_type use, vector_type &w) const;
          virtual void unapply_preconditioner_right(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void unapply_preconditioner_right(matrix_usage_type use, vector_type &w) const;
       public:
          indirect_split_triangular_multilevel_preconditioner();
          virtual ~indirect_split_triangular_multilevel_preconditioner();
          virtual void clear();  // resize everything to 0
          virtual void init(Integer memory_max_level);
          virtual matrix_type extract_left_matrix(Integer k) const;
          virtual matrix_type extract_right_matrix(Integer k) const;
          virtual vector_type extract_middle_matrix(Integer k) const;
          virtual index_list extract_permutation_rows(Integer k) const;
          virtual index_list extract_permutation_columns(Integer k) const;
          virtual index_list extract_inverse_permutation_rows(Integer k) const;
          virtual index_list extract_inverse_permutation_columns(Integer k) const;
          virtual vector_dense<T> extract_left_scaling(Integer k) const;
          virtual vector_dense<T> extract_right_scaling(Integer k) const;
          virtual Integer levels() const;
          virtual Integer left_nnz(Integer k) const;
          virtual Integer right_nnz(Integer k) const;
          virtual Integer total_nnz(Integer k) const;
          virtual Real memory() const;
          virtual Real memory(Integer k) const;
          virtual Integer dim(Integer k) const;
          virtual void print_dimensions() const;
          virtual void write_abs_diagonal(std::string filename) const;
          virtual void write_abs_diagonal_with_indices(std::string filename) const;
          virtual Integer number_small_pivots(Real tau) const;
          virtual Integer left_nnz() const;
          virtual Integer right_nnz() const;
          virtual Integer middle_nnz() const;
          virtual Integer total_nnz() const;
          virtual matrix_type left_preconditioning_matrix(Integer k);
          virtual matrix_type right_preconditioning_matrix(Integer k);
          virtual void print(Integer k) const;
          virtual void print_info(Integer k) const;
          virtual void print_info() const;
          virtual void print() const;
          virtual void read_binary(std::string filename) = 0;
          virtual void write_binary(std::string filename) const = 0;
  };



template <class T, class matrix_type, class vector_type>
  class indirect_split_pseudo_triangular_preconditioner : public split_preconditioner <T,matrix_type, vector_type>
  {
       protected:
          matrix_type Precond_left;     // the left preconditioning matrix
          matrix_type Precond_right;    // the right preconditioning matrix
          special_matrix_type left_form;
          special_matrix_type right_form;
          perm_usage_type left_matrix_usage;
          perm_usage_type right_matrix_usage;
          index_list permutation;
          index_list permutation2;
          virtual void apply_preconditioner_left(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void apply_preconditioner_left(matrix_usage_type use, vector_type &w) const;
          virtual void apply_preconditioner_right(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void apply_preconditioner_right(matrix_usage_type use,vector_type &w) const;
          virtual void unapply_preconditioner_left(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void unapply_preconditioner_left(matrix_usage_type use,vector_type &w) const;
          virtual void unapply_preconditioner_right(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void unapply_preconditioner_right(matrix_usage_type use,vector_type &w) const;
       public:
          indirect_split_pseudo_triangular_preconditioner();
          virtual ~indirect_split_pseudo_triangular_preconditioner();
          virtual matrix_type extract_left_matrix() const;
          virtual matrix_type extract_right_matrix() const ;
          virtual Integer left_nnz() const;
          virtual Integer right_nnz() const;
          virtual Integer total_nnz() const;
          virtual matrix_type& left_preconditioning_matrix();
          virtual matrix_type& right_preconditioning_matrix();
          virtual void print_info() const;
          virtual index_list extract_permutation() const;
          virtual index_list extract_permutation2() const;
          virtual void eliminate_permutations(matrix_type& A, vector_type &b);
          virtual void read_binary(std::string filename) = 0;
          virtual void write_binary(std::string filename) const = 0;
  };





//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: generic_split_preconditioner                                                                       //
//                                                                                                                       //
//***********************************************************************************************************************//

template <class T, class matrix_type, class vector_type>
  class generic_split_preconditioner : public split_preconditioner <T,matrix_type, vector_type>
  {
       protected:
          matrix_type Precond_left;     // the left preconditioning matrix
          matrix_type Precond_right;    // the right preconditioning matrix
          preconditioner_matrix_type left_matrix_usage;
          preconditioner_matrix_type right_matrix_usage;
          special_matrix_type left_matrix_shape;
          special_matrix_type right_matrix_shape;
          virtual void apply_preconditioner_left(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void apply_preconditioner_left(matrix_usage_type use, vector_type &w) const;
          virtual void apply_preconditioner_right(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void apply_preconditioner_right(matrix_usage_type use,vector_type &w) const;
          virtual void unapply_preconditioner_left(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void unapply_preconditioner_left(matrix_usage_type use, vector_type &w) const;
          virtual void unapply_preconditioner_right(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void unapply_preconditioner_right(matrix_usage_type use,vector_type &w) const;
       public:
          generic_split_preconditioner();
          virtual ~generic_split_preconditioner();
          virtual matrix_type extract_left_matrix() const;
          virtual matrix_type extract_right_matrix() const;
          virtual Integer left_nnz() const;
          virtual Integer right_nnz() const;
          virtual Integer total_nnz() const;
          virtual matrix_type& left_preconditioning_matrix();
          virtual matrix_type& right_preconditioning_matrix();
          virtual void print_info() const;
          virtual void read_binary(std::string filename) = 0;
          virtual void write_binary(std::string filename) const = 0;
  };


//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: NullPrecondioner: does not precondition.                                                           //
//                                                                                                                       //
//***********************************************************************************************************************//

template <class T, class matrix_type, class vector_type>
  class NullPreconditioner : public single_preconditioner <T,matrix_type, vector_type>
  {
       protected:
          virtual void apply_preconditioner(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void apply_preconditioner(matrix_usage_type use, vector_type &w) const;
          virtual void unapply_preconditioner(matrix_usage_type use, const vector_type &v, vector_type &w) const;
          virtual void unapply_preconditioner(matrix_usage_type use, vector_type &w) const;
       public:
          NullPreconditioner();
          NullPreconditioner(Integer m, Integer n);
          virtual ~NullPreconditioner();
          virtual void read_binary(std::string filename);
          virtual void write_binary(std::string filename) const;
          virtual void print_info() const;
          virtual Integer total_nnz() const;
  };





//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: ILUC Preconditioner (Saad):                                                                         //
//                                                                                                                       //
//***********************************************************************************************************************//


template <class T, class matrix_type, class vector_type>
  class ILUCPreconditioner : public indirect_split_triangular_preconditioner <T,matrix_type, vector_type>
  {
       public:
          ILUCPreconditioner();
          ILUCPreconditioner(const matrix_type &A, Integer max_fill_in, Real threshold);  // default threshold=-1.0
          ILUCPreconditioner(const matrix_type &A, const ILUC_precond_parameter& p);
          ILUCPreconditioner(const ILUCPreconditioner &A);
          ILUCPreconditioner& operator = (const ILUCPreconditioner<T, matrix_type, vector_type> &A);
          virtual bool exists() const;
          virtual void print_existence();
          virtual void write_binary(std::string filename) const;
          virtual void write_binary(std::string directory, const ILUC_precond_parameter& p) const;
          virtual void read_binary(std::string filename);
  };






template <class T, class matrix_type, class vector_type>
  class ILUTPreconditioner : public indirect_split_triangular_preconditioner <T,matrix_type, vector_type>
  {
       public:
          ILUTPreconditioner();
          ILUTPreconditioner(const matrix_type &A, Integer max_fill_in, Real threshold); // default threshold=1000
          ILUTPreconditioner(const matrix_type &A, const ILUT_precond_parameter& p);
          ILUTPreconditioner(const ILUTPreconditioner &A);
          ILUTPreconditioner& operator = (const ILUTPreconditioner<T,matrix_type, vector_type> &A);
          virtual bool exists() const;
          virtual std::string special_info() const;
          virtual void print_existence();
          virtual void write_binary(std::string filename) const;
          virtual void write_binary(std::string directory, const ILUT_precond_parameter& p) const;
          virtual void read_binary(std::string filename);
          virtual Integer left_nnz() const;
          virtual Integer right_nnz() const;
          virtual Integer total_nnz() const;
  };


//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: ILUTP Preconditioner (Saad):                                                                       //
//                                                                                                                       //
//***********************************************************************************************************************//


template <class T, class matrix_type, class vector_type>
  class ILUTPPreconditioner : public indirect_split_pseudo_triangular_preconditioner <T,matrix_type, vector_type>
  {
       private:
          Integer zero_pivots;
       public:
          ILUTPPreconditioner();
          ILUTPPreconditioner(const matrix_type &A, Integer max_fill_in, Real threshold, Real pt, Integer rp); // default threshold=-1.0, pt = 0.0,  rp=0
          ILUTPPreconditioner(const matrix_type &A, const ILUTP_precond_parameter& p);
          ILUTPPreconditioner(const ILUTPPreconditioner &A);
          ILUTPPreconditioner& operator = (const ILUTPPreconditioner<T,matrix_type, vector_type> &A);
          virtual bool exists() const;
          virtual Integer zero_pivots_encountered();
          virtual std::string special_info() const;
          virtual void print_existence();
          virtual void write_binary(std::string filename) const;
          virtual void read_binary(std::string filename);
          virtual Integer left_nnz() const;
          virtual Integer right_nnz() const;
          virtual Integer total_nnz() const;
  };


//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: ILUCP Preconditioner:                                                                              //
//                                                                                                                       //
//***********************************************************************************************************************//


template <class T, class matrix_type, class vector_type>
  class ILUCPPreconditioner : public indirect_split_pseudo_triangular_preconditioner <T,matrix_type, vector_type>
  {
       private:
          Integer zero_pivots;
       public:
          ILUCPPreconditioner();
          ILUCPPreconditioner(const matrix_type &Acol, Integer max_fill_in, Real threshold, Real perm_tol, Integer rp); // default threshold=-1.0, perm_tol=0.0, rp = -1
          ILUCPPreconditioner(const matrix_type &Acol, const ILUCP_precond_parameter& p);
          ILUCPPreconditioner(const ILUCPPreconditioner &A);
          ILUCPPreconditioner& operator = (const ILUCPPreconditioner<T,matrix_type, vector_type> &A);
          virtual bool exists() const;
          virtual Integer zero_pivots_encountered();
          virtual std::string special_info() const;
          virtual void print_existence();
          virtual void write_binary(std::string filename) const;
          virtual void read_binary(std::string filename);
  };


//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: ILUCDP Preconditioner:                                                                             //
//                                                                                                                       //
//***********************************************************************************************************************//


template <class T, class matrix_type, class vector_type>
  class ILUCDPPreconditioner : public indirect_split_pseudo_triangular_preconditioner <T,matrix_type, vector_type>
  {
       private:
          Integer zero_pivots;
       public:
          ILUCDPPreconditioner();
          ILUCDPPreconditioner(const matrix_type &Arow, const matrix_type &Acol, Integer max_fill_in, Real threshold, Real perm_tol, Integer bpr); // default: threshold=1000.0, perm_tol=1000.0, bpr = -1
          ILUCDPPreconditioner(const matrix_type &Arow, const matrix_type &Acol, matrix_type &Anew, Integer max_fill_in, Real threshold, Real perm_tol, Integer); // default: threshold=1000.0, perm_tol=1000.0, bpr = -1
          ILUCDPPreconditioner(const matrix_type &Arow, const matrix_type &Acol, const ILUCDP_precond_parameter& p);
          ILUCDPPreconditioner(const ILUCDPPreconditioner &A);
          ILUCDPPreconditioner& operator = (const ILUCDPPreconditioner<T,matrix_type, vector_type> &A);
          virtual bool exists() const;
          virtual Integer zero_pivots_encountered();
          virtual std::string special_info() const;
          virtual void print_existence();
          virtual void write_binary(std::string filename) const;
          virtual void read_binary(std::string filename);
  };


//***********************************************************************************************************************//
//                                                                                                                       //
//         The class: multilevelILUCDP Preconditioner:                                                                   //
//                                                                                                                       //
//***********************************************************************************************************************//


template <class T, class matrix_type, class vector_type>
  class multilevelILUCDPPreconditioner : public indirect_split_triangular_multilevel_preconditioner <T,matrix_type, vector_type>
  {
       private:
          array<Integer> zero_pivots;
          iluplusplus_precond_parameter param;
          Integer dim_zero_matrix_factored;
       public:
          multilevelILUCDPPreconditioner();
          virtual ~multilevelILUCDPPreconditioner();
          multilevelILUCDPPreconditioner(const multilevelILUCDPPreconditioner &A);
          multilevelILUCDPPreconditioner& operator = (const multilevelILUCDPPreconditioner<T,matrix_type, vector_type> &A);
          virtual void init(Integer mem_levels);
          virtual bool exists() const;
          virtual iluplusplus_precond_parameter extract_parameters() const;
          virtual Integer dimension_zero_matrix_factored() const;
          virtual Integer zero_pivots_encountered(Integer k) const;
          virtual Integer zero_pivots_encountered() const;
          virtual std::string special_info() const;
          virtual void print_existence() const;
          virtual void write_binary(std::string filename) const;
          virtual void read_binary(std::string filename);
          virtual void make_preprocessed_multilevelILUCDP(const matrix_type &A, const iluplusplus_precond_parameter& IP);
          virtual void make_preprocessed_multilevelILUCDP(T* Adata, Integer* Aindices, Integer* Apointer, Integer Adim, Integer Annz, orientation_type Aorient, const iluplusplus_precond_parameter& IP);
          virtual void make_preprocessed_multilevelILUCDP(std::vector<T>& Adata, std::vector<Integer>& Aindices, std::vector<Integer>& Apointer, orientation_type Aorient, const iluplusplus_precond_parameter& IP);
          // only for testing purposes.
          virtual void make_single_level_of_preprocessed_multilevelILUCDP(const matrix_type &Arow, const iluplusplus_precond_parameter& IP, bool force_finish, matrix_type& Acoarse, Real threshold);
          virtual void make_single_level_of_preprocessed_multilevelILUCDP(const matrix_type &Arow, const iluplusplus_precond_parameter& IP, bool force_finish, matrix_type& Acoarse); 

  };



} // end namespace iluplusplus


#endif
