#include "polymake_includes.h"

#include "polymake_tools.h"

#include "polymake_functions.h"

#include "polymake_type_modules.h"

void polymake_module_add_sparsematrix(jlcxx::Module& polymake)
{

    polymake.method("_get_global_epsilon", []() { return pm::spec_object_traits<double>::global_epsilon; });
    polymake.method("_set_global_epsilon", [](double e) { pm::spec_object_traits<double>::global_epsilon = e; });
    polymake
        .add_type<jlcxx::Parametric<jlcxx::TypeVar<1>>, jlcxx::ParameterList<jlcxx::TypeVar<1>,int>>(
            "SparseMatrix", jlcxx::julia_type("AbstractSparseMatrix", "SparseArrays"))
            .apply_combination<pm::SparseMatrix, VecOrMat_supported::value_type>(
                [](auto wrapped) {
                    typedef typename decltype(wrapped)::type matType;
                    typedef typename decltype(wrapped)::type::value_type elemType;
                    wrapped.template constructor<int64_t, int64_t>();
                    wrapped.method("_getindex",
                        [](const matType& M, int64_t i, int64_t j) {
                            return elemType(M(i - 1, j - 1));
                    });
                    wrapped.method("_setindex!",
                        [](matType& M, const elemType& r, int64_t i,
                        int64_t j) {
                            M(i - 1, j - 1) = r;
                    });
                    wrapped.method("nrows", &matType::rows);
                    wrapped.method("ncols", &matType::cols);
                    wrapped.method("nzindices", [](const matType& S) {
                        return Array<Set<pm::Int>>(pm::rows(pm::index_matrix(S)));
                    });
                    wrapped.method("resize!", [](matType& M, int64_t i,
                                                int64_t j) { M.resize(i, j); });
                    wrapped.method("take",
                                   [](pm::perl::BigObject p, const std::string& s,
                                      const matType& M) { p.take(s) << M; });
                    wrapped.method("show_small_obj", [](const matType& S) {
                        return show_small_object<matType>(S);
                    });
            });
    polymake.method("to_sparsematrix_rational",
        [](pm::perl::PropertyValue pv) {
            return to_SmallObject<pm::SparseMatrix<pm::Rational>>(pv);
    });
    polymake.method("to_sparsematrix_integer",
        [](pm::perl::PropertyValue pv) {
            return to_SmallObject<pm::SparseMatrix<pm::Integer>>(pv);
    });
    polymake.method("to_sparsematrix_int",
        [](pm::perl::PropertyValue pv) {
            return to_SmallObject<pm::SparseMatrix<pm::Int>>(pv);
    });
    polymake.method("to_sparsematrix_double",
        [](pm::perl::PropertyValue pv) {
            return to_SmallObject<pm::SparseMatrix<double>>(pv);
    });
}
