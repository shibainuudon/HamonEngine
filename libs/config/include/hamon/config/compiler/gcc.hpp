/**
 *	@file	gcc.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONFIG_COMPILER_GCC_HPP
#define HAMON_CONFIG_COMPILER_GCC_HPP

#define HAMON_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

#define HAMON_COMPILER "gcc"
#define HAMON_COMPILER_VERSION HAMON_GCC_VERSION

#if !defined(__CUDACC__)
#define HAMON_GCC HAMON_GCC_VERSION
#endif

// HAMON_CXX_STANDARD
#if !defined(HAMON_CXX_STANDARD)
#  if __cplusplus > 201703L
#    define HAMON_CXX_STANDARD 20
#  elif __cplusplus >= 201703L
#    define HAMON_CXX_STANDARD 17
#  elif __cplusplus >= 201402L
#    define HAMON_CXX_STANDARD 14
#  elif  __cplusplus >= 201103L
#    define HAMON_CXX_STANDARD 11
#  else
#    define HAMON_CXX_STANDARD  3
#  endif
#endif  // HAMON_CXX_STANDARD

#if __GNUC__ == 3
#  if defined (__PATHSCALE__)
#     define HAMON_NO_TWO_PHASE_NAME_LOOKUP
#     define HAMON_NO_IS_ABSTRACT
#  endif

#  if __GNUC_MINOR__ < 4
#     define HAMON_NO_IS_ABSTRACT
#  endif
#endif
#if __GNUC__ < 4
//
// All problems to gcc-3.x and earlier here:
//
#define HAMON_NO_TWO_PHASE_NAME_LOOKUP
#  ifdef __OPEN64__
#     define HAMON_NO_IS_ABSTRACT
#  endif
#endif

// GCC prior to 3.4 had #pragma once too but it didn't work well with filesystem links
#if HAMON_GCC_VERSION >= 30400
#define HAMON_HAS_PRAGMA_ONCE
#endif

#if HAMON_GCC_VERSION < 40400
// Previous versions of GCC did not completely implement value-initialization:
// GCC Bug 30111, "Value-initialization of POD base class doesn't initialize
// members", reported by Jonathan Wakely in 2006,
// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=30111 (fixed for GCC 4.4)
// GCC Bug 33916, "Default constructor fails to initialize array members",
// reported by Michael Elizabeth Chastain in 2007,
// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=33916 (fixed for GCC 4.2.4)
// See also: http://www.boost.org/libs/utility/value_init.htm#compiler_issues
#define HAMON_NO_COMPLETE_VALUE_INITIALIZATION
#endif

#if !defined(__EXCEPTIONS) && !defined(HAMON_NO_EXCEPTIONS)
# define HAMON_NO_EXCEPTIONS
#endif

//
// Threading support: Turn this on unconditionally here (except for
// those platforms where we can know for sure). It will get turned off again
// later if no threading API is detected.
//
#if !defined(__MINGW32__) && !defined(linux) && !defined(__linux) && !defined(__linux__)
# define HAMON_HAS_THREADS
#endif

//
// gcc implements the named return value optimization since version 3.1
//
#define HAMON_HAS_NRVO

//
// RTTI and typeinfo detection is possible post gcc-4.3:
//
#if HAMON_GCC_VERSION > 40300
#  ifndef __GXX_RTTI
#     ifndef HAMON_NO_TYPEID
#        define HAMON_NO_TYPEID
#     endif
#     ifndef HAMON_NO_RTTI
#        define HAMON_NO_RTTI
#     endif
#  endif
#endif


// C++11
#if (HAMON_CXX_STANDARD >= 11)
#  if (HAMON_GCC_VERSION >= 40300) && defined(__cpp_rvalue_references) && (__cpp_rvalue_references >= 200610)
#    define HAMON_HAS_CXX11_RVALUE_REFERENCES
#  endif
#  if (HAMON_GCC_VERSION >= 40801) && defined(__cpp_ref_qualifiers) && (__cpp_ref_qualifiers >= 200710)
#    define HAMON_HAS_CXX11_REF_QUALIFIERS
#  endif
#  if (HAMON_GCC_VERSION >= 40700) && defined(__cpp_nsdmi) && (__cpp_nsdmi >= 200809)
#    define HAMON_HAS_CXX11_NSDMI
#  endif
#  if (HAMON_GCC_VERSION >= 40300) && defined(__cpp_variadic_templates) && (__cpp_variadic_templates >= 200704)
#    define HAMON_HAS_CXX11_VARIADIC_TEMPLATES
#  endif
#  if (HAMON_GCC_VERSION >= 40400) && defined(__cpp_initializer_lists) && (__cpp_initializer_lists >= 200806)
#    define HAMON_HAS_CXX11_INITIALIZER_LISTS
#  endif
#  if (HAMON_GCC_VERSION >= 40300) && defined(__cpp_static_assert) && (__cpp_static_assert >= 200410)
#    define HAMON_HAS_CXX11_STATIC_ASSERT
#  endif
#  if (HAMON_GCC_VERSION >= 40400)
#    define HAMON_HAS_CXX11_AUTO_DECLARATIONS
#  endif
#  if (HAMON_GCC_VERSION >= 40400)
#    define HAMON_HAS_CXX11_TRAILING_RETURN_TYPE
#  endif
#  if (HAMON_GCC_VERSION >= 40500) && defined(__cpp_lambdas) && (__cpp_lambdas >= 200907)
#    define HAMON_HAS_CXX11_LAMBDAS
#  endif
#  if (HAMON_GCC_VERSION >= 40300) && defined(__cpp_decltype) && (__cpp_decltype >= 200707)
#    define HAMON_HAS_CXX11_DECLTYPE
#  endif
#  if (HAMON_GCC_VERSION >= 40300)
#    define HAMON_HAS_CXX11_RIGHT_ANGLE_BRACKETS
#  endif
#  if (HAMON_GCC_VERSION >= 40300)
#    define HAMON_HAS_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#  endif
#  if (HAMON_GCC_VERSION >= 40300)
#    define HAMON_HAS_CXX11_SFINAE_EXPR
#  endif
#  if (HAMON_GCC_VERSION >= 40700) && defined(__cpp_alias_templates) && (__cpp_alias_templates >= 200704)
#    define HAMON_HAS_CXX11_ALIAS_TEMPLATES
#  endif
#  if (HAMON_GCC_VERSION >= 40000)
#    define HAMON_HAS_CXX11_EXTERN_TEMPLATE
#  endif
#  if (HAMON_GCC_VERSION >= 40600)
#    define HAMON_HAS_CXX11_NULLPTR
#  endif
#  if (HAMON_GCC_VERSION >= 40400)
#    define HAMON_HAS_CXX11_SCOPED_ENUMS
#  endif
#  if (HAMON_GCC_VERSION >= 40600)
#    define HAMON_HAS_CXX11_FORWARD_DECLARE_ENUMS
#  endif
#  if (HAMON_GCC_VERSION >= 40800) && defined(__cpp_attributes) && (__cpp_attributes >= 200809)
#    define HAMON_HAS_CXX11_ATTRIBUTES
#  endif
#  if (HAMON_GCC_VERSION >= 40800) && (HAMON_HAS_CPP_ATTRIBUTE(noreturn) >= 200809)
#    define HAMON_HAS_CXX11_NORETURN
#  endif
#  if (HAMON_GCC_VERSION >= 40800) && (HAMON_HAS_CPP_ATTRIBUTE(carries_dependency) >= 200809)
#    define HAMON_HAS_CXX11_CARRIES_DEPENDENCY
#  endif
#  if (HAMON_GCC_VERSION >= 40600) && defined(__cpp_constexpr) && (__cpp_constexpr >= 200704)
#    define HAMON_HAS_CXX11_CONSTEXPR
#  endif
#  if (HAMON_GCC_VERSION >= 40800)
#    define HAMON_HAS_CXX11_ALIGNAS
#    define HAMON_HAS_CXX11_ALIGNOF
#  endif
#  if (HAMON_GCC_VERSION >= 40700) && defined(__cpp_delegating_constructors) && (__cpp_delegating_constructors >= 200604)
#    define HAMON_HAS_CXX11_DELEGATING_CONSTRUCTORS
#  endif
#  if (HAMON_GCC_VERSION >= 40800) && defined(__cpp_inheriting_constructors) && (__cpp_inheriting_constructors >= 200802)
#    define HAMON_HAS_CXX11_INHERITING_CONSTRUCTORS
#  endif
#  if (HAMON_GCC_VERSION >= 40500)
#    define HAMON_HAS_CXX11_EXPLICIT_CONVERSION_OPERATORS
#  endif
#  if (HAMON_GCC_VERSION >= 40400) && defined(__cpp_unicode_characters) && (__cpp_unicode_characters >= 200704)
#    define HAMON_HAS_CXX11_CHAR16_T
#    define HAMON_HAS_CXX11_CHAR32_T
#  endif
#  if (HAMON_GCC_VERSION >= 40500) && defined(__cpp_unicode_literals) && (__cpp_unicode_literals >= 200710)
#    define HAMON_HAS_CXX11_UNICODE_LITERALS
#  endif
#  if (HAMON_GCC_VERSION >= 40500) && defined(__cpp_raw_strings) && (__cpp_raw_strings >= 200710)
#    define HAMON_HAS_CXX11_RAW_STRINGS
#  endif
#  if (HAMON_GCC_VERSION >= 40500)
#    define HAMON_HAS_CXX11_UNIVERSAL_CHARACTER_NAME
#  endif
#  if (HAMON_GCC_VERSION >= 40700) && defined(__cpp_user_defined_literals) && (__cpp_user_defined_literals >= 200809)
#    define HAMON_HAS_CXX11_USER_DEFINED_LITERALS
#  endif
#  if (HAMON_GCC_VERSION >= 40400)
#    define HAMON_HAS_CXX11_DELETED_FUNCTIONS
#    define HAMON_HAS_CXX11_DEFAULTED_FUNCTIONS
#  endif
#  if (HAMON_GCC_VERSION >= 40700)
#    define HAMON_HAS_CXX11_EXTENDED_FRIEND_DECLARATIONS
#  endif
#  if (HAMON_GCC_VERSION >= 40400)
#    define HAMON_HAS_CXX11_EXTENDED_SIZEOF
#  endif
#  if (HAMON_GCC_VERSION >= 40400)
#    define HAMON_HAS_CXX11_INLINE_NAMESPACES
#  endif
#  if (HAMON_GCC_VERSION >= 40600)
#    define HAMON_HAS_CXX11_UNRESTRICTED_UNIONS
#  endif
#  if (HAMON_GCC_VERSION >= 40500)
#    define HAMON_HAS_CXX11_LOCAL_TYPE_TEMPLATE_ARGS
#  endif
#  if (HAMON_GCC_VERSION >= 40600) && defined(__cpp_range_based_for) && (__cpp_range_based_for >= 200907)
#    define HAMON_HAS_CXX11_RANGE_BASED_FOR
#  endif
#  if (HAMON_GCC_VERSION >= 40700)
#    define HAMON_HAS_CXX11_OVERRIDE
#    define HAMON_HAS_CXX11_FINAL
#  endif
#  if (HAMON_GCC_VERSION >= 40600)
#    define HAMON_HAS_CXX11_NOEXCEPT
#  endif
#  if (HAMON_GCC_VERSION >= 40800)
#    define HAMON_HAS_CXX11_THREAD_LOCAL
#  endif
#  if (HAMON_GCC_VERSION >= 40300) && defined(__cpp_threadsafe_static_init) && (__cpp_threadsafe_static_init >= 200806)
#    define HAMON_HAS_CXX11_THREADSAFE_STATIC_INIT
#  endif
#  if (HAMON_GCC_VERSION >= 40300)
#    define HAMON_HAS_CXX11_LONG_LONG
#  endif
#  if (HAMON_GCC_VERSION >= 40300)
#    define HAMON_HAS_CXX11_VARIADIC_MACROS
#    define HAMON_HAS_CXX11_PRAGMA_OPERATOR
#  endif
#endif

#define HAMON_HAS_CXX11_UNIFORM_INITIALIZATION

// C++14
#if (HAMON_CXX_STANDARD >= 14)
#  if (HAMON_GCC_VERSION >= 40900) && defined(__cpp_binary_literals) && (__cpp_binary_literals >= 201304)
#    define HAMON_HAS_CXX14_BINARY_LITERALS
#  endif
#  if (HAMON_GCC_VERSION >= 40800) && defined(__cpp_decltype_auto) && (__cpp_decltype_auto >= 201304)
#    define HAMON_HAS_CXX14_DECLTYPE_AUTO
#  endif
#  if (HAMON_GCC_VERSION >= 40900) && defined(__cpp_return_type_deduction) && (__cpp_return_type_deduction >= 201304)
#    define HAMON_HAS_CXX14_RETURN_TYPE_DEDUCTION
#  endif
#  if (HAMON_GCC_VERSION >= 40900) && defined(__cpp_init_captures) && (__cpp_init_captures >= 201304)
#    define HAMON_HAS_CXX14_INIT_CAPTURES
#  endif
#  if (HAMON_GCC_VERSION >= 40900) && defined(__cpp_generic_lambdas) && (__cpp_generic_lambdas >= 201304)
#    define HAMON_HAS_CXX14_GENERIC_LAMBDAS
#  endif
#  if (HAMON_GCC_VERSION >= 40900) && (HAMON_HAS_CPP_ATTRIBUTE(deprecated) >= 201309)
#    define HAMON_HAS_CXX14_DEPRECATED
#  endif
#  if (HAMON_GCC_VERSION >= 50000) && defined(__cpp_sized_deallocation) && (__cpp_sized_deallocation >= 201309)
#    define HAMON_HAS_CXX14_SIZED_DEALLOCATION
#  endif
#  if (HAMON_GCC_VERSION >= 40900) && defined(__cpp_digit_separator) && (__cpp_digit_separator >= 201309)
#    define HAMON_HAS_CXX14_DIGIT_SEPARATORS
#  endif
#  if (HAMON_GCC_VERSION >= 50000) && defined(__cpp_variable_templates) && (__cpp_variable_templates >= 201304)
#    define HAMON_HAS_CXX14_VARIABLE_TEMPLATES
#  endif
#  if (HAMON_GCC_VERSION >= 50000) && defined(__cpp_constexpr) && (__cpp_constexpr >= 201304)
#    define HAMON_HAS_CXX14_CONSTEXPR
#  endif
#  if (HAMON_GCC_VERSION >= 50000) && defined(__cpp_aggregate_nsdmi) && (__cpp_aggregate_nsdmi >= 201304)
#    define HAMON_HAS_CXX14_AGGREGATE_NSDMI
#  endif
#endif

// C++17
#if (HAMON_CXX_STANDARD >= 17)
#  if (HAMON_GCC_VERSION >= 30000) && defined(__cpp_hex_float) && (__cpp_hex_float >= 201603)
#    define HAMON_HAS_CXX17_HEX_FLOAT
#  endif
#  if (HAMON_GCC_VERSION >= 60000) && defined(__cpp_unicode_characters) && (__cpp_unicode_characters >= 201411)
#    define HAMON_HAS_CXX17_U8_CHARACTER_LITERALS
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && defined(__cpp_inline_variables) && (__cpp_inline_variables >= 201606)
#    define HAMON_HAS_CXX17_INLINE_VARIABLES
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && defined(__cpp_aligned_new) && (__cpp_aligned_new >= 201606)
#    define HAMON_HAS_CXX17_ALIGNED_NEW
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && defined(__cpp_guaranteed_copy_elision) && (__cpp_guaranteed_copy_elision >= 201606)
#    define HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && defined(__cpp_noexcept_function_type) && (__cpp_noexcept_function_type >= 201510)
#    define HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE
#  endif
#  if (HAMON_GCC_VERSION >= 70000)
#    define HAMON_HAS_CXX17_EXPRESSION_EVALUATION_ORDER
#  endif
#  if (HAMON_GCC_VERSION >= 60000) && defined(__cpp_fold_expressions) && (__cpp_fold_expressions >= 201411)
#    define HAMON_HAS_CXX17_FOLD_EXPRESSIONS
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && defined(__cpp_capture_star_this) && (__cpp_capture_star_this >= 201603)
#    define HAMON_HAS_CXX17_CAPTURE_STAR_THIS
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && defined(__cpp_constexpr) && (__cpp_constexpr >= 201603)
#    define HAMON_HAS_CXX17_CONSTEXPR_LAMBDA
#    define HAMON_HAS_CXX17_CONSTEXPR
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && defined(__cpp_if_constexpr) && (__cpp_if_constexpr >= 201606)
#    define HAMON_HAS_CXX17_IF_CONSTEXPR
#  endif
#  if (HAMON_GCC_VERSION >= 70000)
#    define HAMON_HAS_CXX17_SELECTION_WITH_INIT
#  endif
#  if (HAMON_GCC_VERSION >= 60000) && defined(__cpp_range_based_for) && (__cpp_range_based_for >= 201603)
#    define HAMON_HAS_CXX17_RANGE_BASED_FOR
#  endif
#  if (HAMON_GCC_VERSION >= 60000) && defined(__cpp_static_assert) && (__cpp_static_assert >= 201411)
#    define HAMON_HAS_CXX17_STATIC_ASSERT
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && defined(__cpp_deduction_guides) && (__cpp_deduction_guides >= 201606)
#    define HAMON_HAS_CXX17_DEDUCTION_GUIDES
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && defined(__cpp_nontype_template_parameter_auto) && (__cpp_nontype_template_parameter_auto >= 201606)
#    define HAMON_HAS_CXX17_NONTYPE_TEMPLATE_PARAMETER_AUTO
#  endif
#  if (HAMON_GCC_VERSION >= 40900) && defined(__cpp_namespace_attributes) && (__cpp_namespace_attributes >= 201411)
#    define HAMON_HAS_CXX17_NAMESPACE_ATTRIBUTES
#  endif
#  if (HAMON_GCC_VERSION >= 60000) && defined(__cpp_enumerator_attributes) && (__cpp_enumerator_attributes >= 201411)
#    define HAMON_HAS_CXX17_ENUMERATOR_ATTRIBUTES
#  endif
#  if (HAMON_GCC_VERSION >= 60000) && defined(__cpp_nested_namespace_definitions) && (__cpp_nested_namespace_definitions >= 201411)
#    define HAMON_HAS_CXX17_NESTED_NAMESPACE_DEFINITIONS
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && defined(__cpp_inheriting_constructors) && (__cpp_inheriting_constructors >= 201511)
#    define HAMON_HAS_CXX17_INHERITING_CONSTRUCTORS
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && defined(__cpp_variadic_using) && (__cpp_variadic_using >= 201611)
#    define HAMON_HAS_CXX17_VARIADIC_USING
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && (HAMON_HAS_CPP_ATTRIBUTE(fallthrough) >= 201603)
#    define HAMON_HAS_CXX17_FALLTHROUGH
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && (HAMON_HAS_CPP_ATTRIBUTE(nodiscard) >= 201603)
#    define HAMON_HAS_CXX17_NODISCARD
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && (HAMON_HAS_CPP_ATTRIBUTE(maybe_unused) >= 201603)
#    define HAMON_HAS_CXX17_MAYBE_UNUSED
#  endif
#  if (HAMON_GCC_VERSION >= 70000)
#    define HAMON_HAS_CXX17_USING_ATTRIBUTE_NAMESPACES
#  endif
#    define HAMON_HAS_CXX17_IGNORING_UNRECOGNIZED_ATTRIBUTES
#  if (HAMON_GCC_VERSION >= 70000) && defined(__cpp_structured_bindings) && (__cpp_structured_bindings >= 201606)
#    define HAMON_HAS_CXX17_STRUCTURED_BINDINGS
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && defined(__cpp_aggregate_bases) && (__cpp_aggregate_bases >= 201603)
#    define HAMON_HAS_CXX17_AGGREGATE_BASES
#  endif
#  if (HAMON_GCC_VERSION >= 70000)
#    define HAMON_HAS_CXX17_INIT_ENUM_CLASS
#  endif
#  if (HAMON_GCC_VERSION >= 50000)
#    define HAMON_HAS_CXX17_TEMPLATE_TEMPLATE_TYPENAME
#  endif
#  if (HAMON_GCC_VERSION >= 60000) && defined(__cpp_nontype_template_args) && (__cpp_nontype_template_args >= 201411)
#    define HAMON_HAS_CXX17_NONTYPE_TEMPLATE_ARGS
#  endif
#  if (HAMON_GCC_VERSION >= 70000) && defined(__cpp_template_template_args) && (__cpp_template_template_args >= 201611)
#    define HAMON_HAS_CXX17_TEMPLATE_TEMPLATE_ARGS
#  endif
#  if (HAMON_GCC_VERSION >= 70000)
#    define HAMON_HAS_CXX17_EXCEPTION_SPECIFICATIONS
#  endif
#  if (HAMON_GCC_VERSION >= 50000) && defined(__has_include)
#    define HAMON_HAS_CXX17_HAS_INCLUDE
#  endif
#endif

#if (HAMON_GCC_VERSION >= 50000)
#  define HAMON_HAS_CXX17_AUTO_DEDUCTION_BRACED_INIT_LIST
#endif

// C++20
#if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX20_ACCESS_CHECKING_ON_SPECIALIZATIONS		// P0692R1
#  if (HAMON_GCC_VERSION >= 50000)
#    define HAMON_HAS_CXX20_FEATURE_TEST_MACROS						// P0941R2
#  endif
#  if (HAMON_GCC_VERSION >= 80000)
#    define HAMON_HAS_CXX20_CAPTURE_COPY_THIS						// P0409R2
#    define HAMON_HAS_CXX20_BITFIELD_DEFAULT_MEMBER_INITIALIZER		// P0683R1
#    define HAMON_HAS_CXX20_CONST_QUALIFIED_POINTERS_TO_MEMBERS		// P0704R1
#    if defined(__cpp_generic_lambdas) && (__cpp_generic_lambdas >= 201707)
#      define HAMON_HAS_CXX20_GENERIC_LAMBDAS						// P0428R2
#    endif
#    if defined(__cpp_designated_initializers) && (__cpp_designated_initializers >= 201707)
#      define HAMON_HAS_CXX20_DESIGNATED_INITIALIZERS				// P0329R4
#    endif
#  endif
#  if (HAMON_GCC_VERSION >= 90000)
#    define HAMON_HAS_CXX20_CONSTEXPR_VIRTUAL_FUNCTION				// P1064R0
#    define HAMON_HAS_CXX20_CONSTEXPR_TRY_CATCH						// P1002R1
#    define HAMON_HAS_CXX20_CONSTEXPR_UNION							// P1330R0
#    define HAMON_HAS_CXX20_LAMBDAS_IN_UNEVALUATED_CONTEXTS			// P0315R4
#    define HAMON_HAS_CXX20_RANGE_BASED_FOR_INITIALIZER				// P0614R1
#    define HAMON_HAS_CXX20_DEFAULT_CONSTRUCTIBLE_AND_ASSIGNABLE_STATELESS_LAMBDAS	// P0624R2
#    define HAMON_HAS_CXX20_CONST_MISMATCH_WITH_DEFAULTED_COPY_CONSTRUCTOR	// P0641R2
#    define HAMON_HAS_CXX20_ADL_AND_FUNCTION_TEMPLATES				// P0846R0
#    define HAMON_HAS_CXX20_OPTIONAL_TYPENAME						// P0634R3
#    define HAMON_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_CLASS		// P0732R2
#    define HAMON_HAS_CXX20_DEPRECATE_IMPLICIT_CAPTURE_COPY_THIS	// P0806R2
#    define HAMON_HAS_CXX20_PROHIBIT_AGGREGATES_WITH_USER_DECLARED_CONSTRUCTORS	// P1008R1
#    define HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED					// P0595R2
#    define HAMON_HAS_CXX20_NESTED_INLINE_NAMESPACES				// P1094R2
#    define HAMON_HAS_CXX20_TWOS_COMPLEMENT_SIGNED_INTEGERS			// P1236R1
#    if (HAMON_HAS_CPP_ATTRIBUTE(likely) >= 201803)
#      define HAMON_HAS_CXX20_LIKELY								// P0479R5
#    endif
#    if (HAMON_HAS_CPP_ATTRIBUTE(unlikely) >= 201803)
#      define HAMON_HAS_CXX20_UNLIKELY								// P0479R5
#    endif
#    if (HAMON_HAS_CPP_ATTRIBUTE(no_unique_address) >= 201803)
#      define HAMON_HAS_CXX20_NO_UNIQUE_ADDRESS						// P0840R2
#    endif
#    if defined(__cpp_constexpr_in_decltype) && (__cpp_constexpr_in_decltype >= 201711)
#      define HAMON_HAS_CXX20_CONSTEXPR_IN_DECLTYPE					// P0859R0
#    endif
#    if defined(__cpp_init_captures) && (__cpp_init_captures >= 201803)
#      define HAMON_HAS_CXX20_INIT_CAPTURES							// P0780R2
#    endif
#    if defined(__cpp_impl_destroying_delete) && (__cpp_impl_destroying_delete >= 201806)
#      define HAMON_HAS_CXX20_DESTROYING_DELETE						// P0722R3
#    endif
#    if defined(__cpp_char8_t) && (__cpp_char8_t >= 201811)
#      define HAMON_HAS_CXX20_CHAR8_T								// P0482R6
#    endif
#    if defined(__cpp_conditional_explicit) && (__cpp_conditional_explicit >= 201806)
#      define HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT					// P0892R2
#    endif
#  endif
#  if (HAMON_GCC_VERSION >= 100000)
#    define HAMON_HAS_CXX20_VA_OPT									// P0306R4, P1042R1
#    define HAMON_HAS_CXX20_DEFAULTING_COMPARISON_BY_VALUE			// P1946R0
#    define HAMON_HAS_CXX20_REMOVE_WEAK_EQUALITY_STRONG_EQUALITY	// P1959R0
#    define HAMON_HAS_CXX20_CONSISTENCY_IMPROVEMENTS_FOR_COMPARISONS	// P1120R0
#    define HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_CAST					// P1327R1
#    define HAMON_HAS_CXX20_CONSTEXPR_TRIVIAL_DEFAULT_INIT			// P1331R2
#    define HAMON_HAS_CXX20_CONSTEXPR_ASM							// P1668R1
#    define HAMON_HAS_CXX20_CONDITIONALLY_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS	// P0848R3
#    define HAMON_HAS_CXX20_ABBREVIATED_FUNCTION_TEMPLATE			// P1141R2
#    define HAMON_HAS_CXX20_STRONGER_UNICODE_REQUIREMENTS			// P1041R4,P1139R2
#    define HAMON_HAS_CXX20_STRUCTURED_BINDING_EXTENSIONS			// P1091R3,P1381R1
#    define HAMON_HAS_CXX20_CONVERSIONS_TO_UNBOUNDED_ARRAY			// P0388R4
#    define HAMON_HAS_CXX20_DEPRECATE_VOLATILE						// P1152R4
#    define HAMON_HAS_CXX20_DEPRECATE_COMMA_IN_SUBSCRIPTING_EXPRESSIONS	// P1161R3
#    if defined(__cpp_impl_coroutine) && (__cpp_impl_coroutine >= 201902)
#      define HAMON_HAS_CXX20_COROUTINES							// P0912R5
#    endif
#    if defined(__cpp_concepts) && (__cpp_concepts >= 201907)
#      define HAMON_HAS_CXX20_CONCEPTS								// P0734R0
#    endif
#    if defined(__cpp_constexpr_dynamic_alloc) && (__cpp_constexpr_dynamic_alloc >= 201907)
#      define HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC				// P0784R7
#    endif
#    if defined(__cpp_impl_three_way_comparison) && (__cpp_impl_three_way_comparison >= 201907)
#      define HAMON_HAS_CXX20_THREE_WAY_COMPARISON					// P0515R3
#      define HAMON_HAS_CXX20_THREE_WAY_COMPARISON_NE_EQ_OP			// P1185R2
#    endif
#    if defined(__cpp_deduction_guides) && (__cpp_deduction_guides >= 201907)
#      define HAMON_HAS_CXX20_CTAD_ALIAS_TEMPLATE					// P1814R0
#    endif
#    if defined(__cpp_constinit) && (__cpp_constinit >= 201907)
#      define HAMON_HAS_CXX20_CONSTINIT								// P1143R2
#    endif
#    if defined(__cpp_aggregate_paren_init) && (__cpp_aggregate_paren_init >= 201902)
#      define HAMON_HAS_CXX20_AGGREGATE_PAREN_INIT					// P0960R3
#    endif
#    if (HAMON_HAS_CPP_ATTRIBUTE(nodiscard) >= 201907)
#      define HAMON_HAS_CXX20_NODISCARD_WITH_MESSAGE				// P1301R4
#      define HAMON_HAS_CXX20_NODISCARD_CTOR						// P1771R1
#    endif
#  endif
#  if (HAMON_GCC_VERSION >= 110000)
#    if defined(__cpp_deduction_guides) && (__cpp_deduction_guides >= 201907)
#      define HAMON_HAS_CXX20_CTAD_AGGREGATE						// P1816R0, P2082R1
#    endif
#    if defined(__cpp_impl_three_way_comparison) && (__cpp_impl_three_way_comparison >= 201907)
#      define HAMON_HAS_CXX20_SYNTHESIZING_THREE_WAY_COMPARISON		// P1186R3
#    endif
#    if defined(__cpp_consteval) && (__cpp_consteval >= 201811)
#      define HAMON_HAS_CXX20_CONSTEVAL								// P1073R3
#    endif
#    if defined(__cpp_using_enum) && (__cpp_using_enum >= 201907)
#      define HAMON_HAS_CXX20_USING_ENUM							// P1099R5
#    endif
#    if defined(__cpp_nontype_template_args) && (__cpp_nontype_template_args >= 201911)
#      define HAMON_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_FLOAT		// P1907R1
#    endif
#  endif
#  if defined(__cpp_constexpr) && (__cpp_constexpr >= 201907)
#    define HAMON_HAS_CXX20_CONSTEXPR
#  endif


#if (HAMON_GCC_VERSION >= 80000)
#  define HAMON_HAS_CXX20_RELAXING_STRUCTURED_BINDINGS				// P0961R1
#  define HAMON_HAS_CXX20_RELAXING_RANGE_FOR						// P0962R1
#  define HAMON_HAS_CXX20_SIMPLIFYING_IMPLICIT_LAMBDA_CAPTURE		// P0588R1
#  define HAMON_HAS_CXX20_STRUCTURED_BINDINGS_TO_ACCESSIBLE_MEMBERS	// P0969R0
#  if (HAMON_CXX_STANDARD >= 17)	// Defect report としてC++17に適用される
#    define HAMON_HAS_CXX20_INITIALIZER_LIST_CTAD					// P0702R1
#  endif
#endif
#if (HAMON_GCC_VERSION >= 100000)
#  define HAMON_HAS_CXX20_EXCEPTION_SPEC_DEFAULTED_FUNCTION			// P1286R2
#  define HAMON_HAS_CXX20_POINTER_TO_BOOL_CONVERTING				// P1957R2
#endif
#if (HAMON_GCC_VERSION >= 110000)
#  define HAMON_HAS_CXX20_ARRAY_SIZE_DEDUCTION_NEW					// P1009R2
#  define HAMON_HAS_CXX20_IMPLICIT_MOVE								// P1825R0
#  define HAMON_HAS_CXX20_PSEUDO_DESTRUCTOR							// P0593R6
#endif

//#define HAMON_HAS_CXX20_MODULES								// P1103R3

#endif

#if defined(__MINGW32__)
// Currently (June 2017) thread_local is broken on mingw for all current compiler releases, see
// https://sourceforge.net/p/mingw-w64/bugs/527/
// Not setting this causes program termination on thread exit.
#  undef HAMON_HAS_CXX11_THREAD_LOCAL
#endif

#endif // HAMON_CONFIG_COMPILER_GCC_HPP
