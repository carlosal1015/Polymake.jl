#include "polymake_includes.h"

#include "polymake_tools.h"

#include "polymake_functions.h"

#include "polymake_type_modules.h"

void polymake_module_add_rational(jlcxx::Module& polymake)
{

    polymake
        .add_type<pm::Rational>("Rational",
                                jlcxx::julia_type("Real", "Base"))
        .constructor<pm::Integer, pm::Integer>()
        .method("rational_si_si", [](
            const jlcxx::StrictlyTypedNumber<long> num,
            const jlcxx::StrictlyTypedNumber<long> den) {
            return pm::Rational(num.value, den.value);
        })
        .method("<", [](const pm::Rational& a, const pm::Rational& b) { return a < b; })
        .method("<", [](const pm::Rational& a, const pm::Integer& b) { return a < b; })
        .method("<", [](const pm::Rational& a,
                        int64_t       b) { return a < static_cast<pm::Int>(b); })
        .method("<", [](const pm::Integer& a, const pm::Rational& b) { return a < b; })
        .method("<", [](int64_t       a,
                        const pm::Rational& b) { return static_cast<pm::Int>(a) < b; })

        .method("<=", [](const pm::Rational& a, const pm::Rational& b) { return a <= b; })
        .method("<=", [](const pm::Rational& a, const pm::Integer& b) { return a <= b; })
        .method("<=", [](const pm::Rational& a,
                         int64_t b) { return a <= static_cast<pm::Int>(b); })
        .method("<=", [](const pm::Integer& a, const pm::Rational& b) { return a <= b; })
        .method("<=", [](int64_t a, const pm::Rational& b) {
                    return static_cast<pm::Int>(a) <= b;
                })

        .method(
            "numerator",
            [](const pm::Rational& r) { return pm::Integer(numerator(r)); })
        .method(
            "denominator",
            [](const pm::Rational& r) { return pm::Integer(denominator(r)); })
        .method("show_small_obj",
                [](const pm::Rational& r) {
                    return show_small_object<pm::Rational>(r, false);
                })
        .method("Float64", [](const pm::Rational& a) { return double(a); })
        .method("-", [](const pm::Rational& a, const pm::Rational& b) { return a - b; })
        .method("-", [](const pm::Rational& a, const pm::Integer& b) { return a - b; })
        .method("-", [](const pm::Rational& a,
                        int64_t       b) { return a - static_cast<pm::Int>(b); })
        .method("-", [](const pm::Integer& a, const pm::Rational& b) { return a - b; })
        .method("-", [](int64_t       a,
                        const pm::Rational& b) { return static_cast<pm::Int>(a) - b; })
        // unary minus
        .method("-", [](const pm::Rational& a) { return -a; })

        .method("//", [](const pm::Rational& a, const pm::Rational& b) { return a / b; })
        .method("//", [](const pm::Rational& a, const pm::Integer&  b) { return a / b; })
        .method("//", [](const pm::Rational& a, int64_t       b) {
            return a / static_cast<pm::Int>(b); })
        .method("//", [](const pm::Integer&  a, const pm::Rational& b) { return a / b; })
        .method("//", [](int64_t       a, const pm::Rational& b) {
            return static_cast<pm::Int>(a) / b; });

        polymake.set_override_module(polymake.julia_module());
        polymake.method("==", [](const pm::Rational& a, const pm::Rational& b) {
            return a == b; });
        polymake.method("==", [](const pm::Rational& a, const pm::Integer& b) {
            return a == b; });
        polymake.method("==", [](const pm::Integer& a, const pm::Rational& b) {
            return a == b; });
        polymake.method("==", [](const pm::Rational& a, int64_t b) {
            return static_cast<pm::Int>(a) == b; });
        polymake.method("==", [](int64_t a, const pm::Rational& b) {
            return a == static_cast<pm::Int>(b); });
        // the symmetric definitions are on the julia side
        polymake.method("+", [](const pm::Rational& a, const pm::Rational& b) {
            return a + b; });
        polymake.method("+", [](const pm::Rational& a, const pm::Integer& b) {
            return a + b; });
        polymake.method("+", [](const pm::Integer& a, const pm::Rational& b) {
            return a + b; });
        polymake.method("+", [](const pm::Rational& a, int64_t b) {
            return a + static_cast<pm::Int>(b); });
        polymake.method("+", [](int64_t a, const pm::Rational& b) {
            return static_cast<pm::Int>(a) + b; });
        polymake.method("*", [](const pm::Rational& a, const pm::Rational& b) {
            return a * b; });
        polymake.method("*", [](const pm::Rational& a, const pm::Integer& b) {
            return a * b; });
        polymake.method("*", [](const pm::Integer& a, const pm::Rational& b) {
            return a * b; });
        polymake.method("*", [](const pm::Rational& a, int64_t b) {
            return a * static_cast<pm::Int>(b); });
        polymake.method("*", [](int64_t a, const pm::Rational& b) {
            return static_cast<pm::Int>(a) * b; });
        polymake.unset_override_module();

    polymake.method("to_rational", [](pm::perl::PropertyValue pv) {
        return to_SmallObject<pm::Rational>(pv);
    });
}
