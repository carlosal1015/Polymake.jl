#include "polymake_includes.h"

#include "polymake_tools.h"

#include "polymake_functions.h"

#include "polymake_type_modules.h"

template<> struct jlcxx::IsMirroredType<pm::Max> : std::false_type { };
template<> struct jlcxx::IsMirroredType<pm::Min> : std::false_type { };

void polymake_module_add_tropicalnumber(jlcxx::Module& polymake)
{
    polymake.add_type<pm::Max>("Max");
    polymake.add_type<pm::Min>("Min");

    polymake
        .add_type<jlcxx::Parametric<jlcxx::TypeVar<1>, jlcxx::TypeVar<2>>>(
            "TropicalNumber", jlcxx::julia_type("Number", "Base"))
            .apply_combination<pm::TropicalNumber,
            jlcxx::ParameterList<pm::Min,pm::Max>,
                jlcxx::ParameterList<pm::Rational>>(
                [](auto wrapped) {
                    typedef typename decltype(wrapped)::type tropType;
                    wrapped.template constructor<pm::Rational>();
                    wrapped.method("zero", [](const tropType& a) { return a.zero(); });
                    wrapped.method("dual_zero", [](const tropType& a) { return a.dual_zero(); });
                    wrapped.method("one", [](const tropType& a) { return a.one(); });
                    wrapped.method("_add", [](const tropType& a, const tropType& b) { return a + b; });
                    wrapped.method("_mul", [](const tropType& a, const tropType& b) { return a * b; });
                    wrapped.method("//", [](const tropType& a, const tropType& b) { return a / b; });
                    wrapped.method("_isequal", [](const tropType& a,
                            const tropType& b) { return a == b; });
                    wrapped.method("<", [](const tropType& a,
                            const tropType& b) { return a < b; });
                    wrapped.method("scalar", [](const tropType& a) { return pm::Rational(a); });
                    wrapped.method("show_small_obj", [](const tropType& S) {
                        return show_small_object<tropType>(S);
                    });
            });
    polymake.method("to_tropicalnumber_max_rational",
        [](pm::perl::PropertyValue pv) {
            return to_SmallObject<pm::TropicalNumber<pm::Max,pm::Rational>>(pv);
        });
    polymake.method("to_tropicalnumber_min_rational",
        [](pm::perl::PropertyValue pv) {
            return to_SmallObject<pm::TropicalNumber<pm::Min,pm::Rational>>(pv);
    });
    // polymake.method("to_tropicalnumber_max_integer",
    //     [](pm::perl::PropertyValue pv) {
    //         return to_SmallObject<pm::TropicalNumber<pm::Max,pm::Integer>>(pv);
    //     });
    // polymake.method("to_tropicalnumber_min_integer",
    //     [](pm::perl::PropertyValue pv) {
    //         return to_SmallObject<pm::TropicalNumber<pm::Min,pm::Integer>>(pv);
    //     });
}
