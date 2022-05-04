/**
 *	@file	clang.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONFIG_COMPILER_CLANG_HPP
#define HAMON_CONFIG_COMPILER_CLANG_HPP

#define HAMON_CLANG_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#define HAMON_CLANG HAMON_CLANG_VERSION

#define HAMON_COMPILER "clang"
#define HAMON_COMPILER_VERSION HAMON_CLANG_VERSION

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

#if !HAMON_HAS_FEATURE(cxx_exceptions) && !defined(HAMON_NO_EXCEPTIONS)
#  define HAMON_NO_EXCEPTIONS
#endif

#if !HAMON_HAS_FEATURE(cxx_rtti) && !defined(HAMON_NO_RTTI)
#  define HAMON_NO_RTTI
#endif

#if !HAMON_HAS_FEATURE(cxx_rtti) && !defined(HAMON_NO_TYPEID)
#  define HAMON_NO_TYPEID
#endif

// C++11
#if (HAMON_CXX_STANDARD >= 11)
#  if defined(__cpp_rvalue_references) && (__cpp_rvalue_references >= 200610)
#    define HAMON_HAS_CXX11_RVALUE_REFERENCES			// N2118
#  endif
#  if defined(__cpp_ref_qualifiers) && (__cpp_ref_qualifiers >= 200710)
#    define HAMON_HAS_CXX11_REF_QUALIFIERS				// N2439
#  endif
#  if defined(__cpp_nsdmi) && (__cpp_nsdmi >= 200809)
#    define HAMON_HAS_CXX11_NSDMI						// N2756
#  endif
#  if defined(__cpp_variadic_templates) && (__cpp_variadic_templates >= 200704)
#    define HAMON_HAS_CXX11_VARIADIC_TEMPLATES			// N2242
#  endif
#  if defined(__cpp_initializer_lists) && (__cpp_initializer_lists >= 200806)
#    define HAMON_HAS_CXX11_INITIALIZER_LISTS			// N2672
#  endif
#  if defined(__cpp_static_assert) && (__cpp_static_assert >= 200410)
#    define HAMON_HAS_CXX11_STATIC_ASSERT				// N1720
#  endif
#  if HAMON_HAS_FEATURE(cxx_auto_type)
#    define HAMON_HAS_CXX11_AUTO_DECLARATIONS			// N2546
#  endif
#  if HAMON_HAS_FEATURE(cxx_trailing_return)
#    define HAMON_HAS_CXX11_TRAILING_RETURN_TYPE		// N2541
#  endif
#  if defined(__cpp_lambdas) && (__cpp_lambdas >= 200907)
#    define HAMON_HAS_CXX11_LAMBDAS					// N2927
#  endif
#  if defined(__cpp_decltype) && (__cpp_decltype >= 200707)
#    define HAMON_HAS_CXX11_DECLTYPE					// N2343
#  endif
#  if (HAMON_CLANG_VERSION >= 20900)
#    define HAMON_HAS_CXX11_RIGHT_ANGLE_BRACKETS		// N1757
#  endif
#  if HAMON_HAS_FEATURE(cxx_default_function_template_args)
#    define HAMON_HAS_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#  endif
#  if (HAMON_CLANG_VERSION >= 20900)
#    define HAMON_HAS_CXX11_SFINAE_EXPR				// N2634
#  endif
#  if defined(__cpp_alias_templates) && (__cpp_alias_templates >= 200704)
#    define HAMON_HAS_CXX11_ALIAS_TEMPLATES			// N2258
#  endif
#  if (HAMON_CLANG_VERSION >= 20900)
#    define HAMON_HAS_CXX11_EXTERN_TEMPLATE			// N1987
#  endif
#  if HAMON_HAS_FEATURE(cxx_nullptr)
#    define HAMON_HAS_CXX11_NULLPTR					// N2431
#  endif
#  if HAMON_HAS_FEATURE(cxx_strong_enums)
#    define HAMON_HAS_CXX11_SCOPED_ENUMS				// N2347
#  endif
#  if (HAMON_CLANG_VERSION >= 30100)
#    define HAMON_HAS_CXX11_FORWARD_DECLARE_ENUMS		// N2764
#  endif
#  if defined(__cpp_attributes) && (__cpp_attributes >= 200809)
#    define HAMON_HAS_CXX11_ATTRIBUTES					// N2761
#  endif
#  if (HAMON_HAS_CPP_ATTRIBUTE(noreturn) >= 200809)
#    define HAMON_HAS_CXX11_NORETURN					// N2761
#  endif
#  if (HAMON_HAS_CPP_ATTRIBUTE(carries_dependency) >= 200809)
#    define HAMON_HAS_CXX11_CARRIES_DEPENDENCY			// N2761
#  endif
#  if defined(__cpp_constexpr) && (__cpp_constexpr >= 200704)
#    define HAMON_HAS_CXX11_CONSTEXPR					// N2235
#  endif
#  if HAMON_HAS_FEATURE(cxx_alignas)
#    define HAMON_HAS_CXX11_ALIGNAS					// N2341
#  endif
#  if (HAMON_CLANG_VERSION >= 30300)
#    define HAMON_HAS_CXX11_ALIGNOF					// N2341
#  endif
#  if defined(__cpp_delegating_constructors) && (__cpp_delegating_constructors >= 200604)
#    define HAMON_HAS_CXX11_DELEGATING_CONSTRUCTORS	// N1986
#  endif
#  if defined(__cpp_inheriting_constructors) && (__cpp_inheriting_constructors >= 200802)
#    define HAMON_HAS_CXX11_INHERITING_CONSTRUCTORS	// N2540
#  endif
#  if HAMON_HAS_FEATURE(cxx_explicit_conversions)
#    define HAMON_HAS_CXX11_EXPLICIT_CONVERSION_OPERATORS	// N2437
#  endif
#  if defined(__cpp_unicode_characters) && (__cpp_unicode_characters >= 200704)
#    define HAMON_HAS_CXX11_CHAR16_T					// N2249
#    define HAMON_HAS_CXX11_CHAR32_T					// N2249
#  endif
#  if defined(__cpp_unicode_literals) && (__cpp_unicode_literals >= 200710)
#    define HAMON_HAS_CXX11_UNICODE_LITERALS			// N2442
#  endif
#  if defined(__cpp_raw_strings) && (__cpp_raw_strings >= 200710)
#    define HAMON_HAS_CXX11_RAW_STRINGS				// N2442
#  endif
#  if (HAMON_CLANG_VERSION >= 30100)
#    define HAMON_HAS_CXX11_UNIVERSAL_CHARACTER_NAME	// N2170
#  endif
#  if defined(__cpp_user_defined_literals) && (__cpp_user_defined_literals >= 200809)
#    define HAMON_HAS_CXX11_USER_DEFINED_LITERALS		// N2765
#  endif
#  if HAMON_HAS_FEATURE(cxx_deleted_functions)
#    define HAMON_HAS_CXX11_DELETED_FUNCTIONS			// N2346
#  endif
#  if HAMON_HAS_FEATURE(cxx_defaulted_functions)
#    define HAMON_HAS_CXX11_DEFAULTED_FUNCTIONS		// N2346
#  endif
#  if (HAMON_CLANG_VERSION >= 20900)
#    define HAMON_HAS_CXX11_EXTENDED_FRIEND_DECLARATIONS	// N1791
#  endif
#  if (HAMON_CLANG_VERSION >= 30100)
#    define HAMON_HAS_CXX11_EXTENDED_SIZEOF			// N2253
#  endif
#  if HAMON_HAS_FEATURE(cxx_inline_namespaces)
#    define HAMON_HAS_CXX11_INLINE_NAMESPACES			// N2535
#  endif
#  if (HAMON_CLANG_VERSION >= 30100)
#    define HAMON_HAS_CXX11_UNRESTRICTED_UNIONS		// N2544
#  endif
#  if HAMON_HAS_FEATURE(cxx_local_type_template_args)
#    define HAMON_HAS_CXX11_LOCAL_TYPE_TEMPLATE_ARGS	// N2657
#  endif
#  if defined(__cpp_range_based_for) && (__cpp_range_based_for >= 200907)
#    define HAMON_HAS_CXX11_RANGE_BASED_FOR			// N2930
#  endif
#  if HAMON_HAS_FEATURE(cxx_override_control)
#    define HAMON_HAS_CXX11_OVERRIDE					// N3272
#    define HAMON_HAS_CXX11_FINAL						// N3272
#  endif
#  if HAMON_HAS_FEATURE(cxx_noexcept)
#    define HAMON_HAS_CXX11_NOEXCEPT					// N3050
#  endif
#  if HAMON_HAS_FEATURE(cxx_thread_local)
#    define HAMON_HAS_CXX11_THREAD_LOCAL				// N2659
#  endif
#  if defined(__cpp_threadsafe_static_init) && (__cpp_threadsafe_static_init >= 200806)
#    define HAMON_HAS_CXX11_THREADSAFE_STATIC_INIT		// N2660
#  endif
#  if (HAMON_CLANG_VERSION >= 20900)
#    define HAMON_HAS_CXX11_LONG_LONG					// N1811
#  endif
#  if (HAMON_CLANG_VERSION >= 20900)
#    define HAMON_HAS_CXX11_VARIADIC_MACROS			// N1653
#    define HAMON_HAS_CXX11_PRAGMA_OPERATOR			// N1653
#  endif
#endif

#define HAMON_HAS_CXX11_UNIFORM_INITIALIZATION		// N2640

// C++14
#if (HAMON_CXX_STANDARD >= 14)
#  if defined(__cpp_binary_literals) && (__cpp_binary_literals >= 201304)
#    define HAMON_HAS_CXX14_BINARY_LITERALS			// N3472
#  endif
#  if defined(__cpp_decltype_auto) && (__cpp_decltype_auto >= 201304)
#    define HAMON_HAS_CXX14_DECLTYPE_AUTO				// N3638
#  endif
#  if defined(__cpp_return_type_deduction) && (__cpp_return_type_deduction >= 201304)
#    define HAMON_HAS_CXX14_RETURN_TYPE_DEDUCTION		// N3638
#  endif
#  if defined(__cpp_init_captures) && (__cpp_init_captures >= 201304)
#    define HAMON_HAS_CXX14_INIT_CAPTURES				// N3610
#  endif
#  if defined(__cpp_generic_lambdas) && (__cpp_generic_lambdas >= 201304)
#    define HAMON_HAS_CXX14_GENERIC_LAMBDAS			// N3649
#  endif
#  if (HAMON_HAS_CPP_ATTRIBUTE(deprecated) >= 201309)
#    define HAMON_HAS_CXX14_DEPRECATED					// N3760
#  endif
#  if defined(__cpp_sized_deallocation) && (__cpp_sized_deallocation >= 201309)
#    define HAMON_HAS_CXX14_SIZED_DEALLOCATION			// N3778
#  endif
#  if defined(__cpp_digit_separator) && (__cpp_digit_separator >= 201309)
#    define HAMON_HAS_CXX14_DIGIT_SEPARATORS			// N3781
#  endif
#  if defined(__cpp_variable_templates) && (__cpp_variable_templates >= 201304)
#    define HAMON_HAS_CXX14_VARIABLE_TEMPLATES			// N3651
#  endif
#  if defined(__cpp_constexpr) && (__cpp_constexpr >= 201304)
#    define HAMON_HAS_CXX14_CONSTEXPR					// N3652
#  endif
#  if defined(__cpp_aggregate_nsdmi) && (__cpp_aggregate_nsdmi >= 201304)
#    define HAMON_HAS_CXX14_AGGREGATE_NSDMI			// N3653
#  endif
#endif

// C++17
#if (HAMON_CXX_STANDARD >= 17)
#  if defined(__cpp_hex_float) && (__cpp_hex_float >= 201603)
#    define HAMON_HAS_CXX17_HEX_FLOAT					// P0245R1
#  endif
#  if defined(__cpp_unicode_characters) && (__cpp_unicode_characters >= 201411)
#    define HAMON_HAS_CXX17_U8_CHARACTER_LITERALS		// N4267
#  endif
#  if defined(__cpp_inline_variables) && (__cpp_inline_variables >= 201606)
#    define HAMON_HAS_CXX17_INLINE_VARIABLES			// P0386R2
#  endif
#  if defined(__cpp_aligned_new) && (__cpp_aligned_new >= 201606)
#    define HAMON_HAS_CXX17_ALIGNED_NEW				// P0035R4
#  endif
#  if defined(__cpp_guaranteed_copy_elision) && (__cpp_guaranteed_copy_elision >= 201606)
#    define HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION	// P0135R1
#  endif
#  if defined(__cpp_noexcept_function_type) && (__cpp_noexcept_function_type >= 201510)
#    define HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE		// P0012R1
#  endif
#  if (HAMON_CLANG_VERSION >= 40000)
#    define HAMON_HAS_CXX17_EXPRESSION_EVALUATION_ORDER	// P0145R3
#  endif
#  if defined(__cpp_fold_expressions) && (__cpp_fold_expressions >= 201411)
#    define HAMON_HAS_CXX17_FOLD_EXPRESSIONS			// N4295
#  endif
#  if defined(__cpp_capture_star_this) && (__cpp_capture_star_this >= 201603)
#    define HAMON_HAS_CXX17_CAPTURE_STAR_THIS			// P0018R3
#  endif
#  if defined(__cpp_constexpr) && (__cpp_constexpr >= 201603)
#    define HAMON_HAS_CXX17_CONSTEXPR_LAMBDA			// P0170R1
#    define HAMON_HAS_CXX17_CONSTEXPR
#  endif
#  if defined(__cpp_if_constexpr) && (__cpp_if_constexpr >= 201606)
#    define HAMON_HAS_CXX17_IF_CONSTEXPR				// P0292R2
#  endif
#  if (HAMON_CLANG_VERSION >= 30900)
#    define HAMON_HAS_CXX17_SELECTION_WITH_INIT		// P0305R1
#  endif
#  if defined(__cpp_range_based_for) && (__cpp_range_based_for >= 201603)
#    define HAMON_HAS_CXX17_RANGE_BASED_FOR			// P0184R0
#  endif
#  if defined(__cpp_static_assert) && (__cpp_static_assert >= 201411)
#    define HAMON_HAS_CXX17_STATIC_ASSERT				// N3928
#  endif
#  if defined(__cpp_deduction_guides) && (__cpp_deduction_guides >= 201606)
#    define HAMON_HAS_CXX17_DEDUCTION_GUIDES			// P0091R3
#  endif
#  if defined(__cpp_nontype_template_parameter_auto) && (__cpp_nontype_template_parameter_auto >= 201606)
#    define HAMON_HAS_CXX17_NONTYPE_TEMPLATE_PARAMETER_AUTO	// P0127R2
#  endif
#  if defined(__cpp_namespace_attributes) && (__cpp_namespace_attributes >= 201411)
#    define HAMON_HAS_CXX17_NAMESPACE_ATTRIBUTES		// N4266
#  endif
#  if defined(__cpp_enumerator_attributes) && (__cpp_enumerator_attributes >= 201411)
#    define HAMON_HAS_CXX17_ENUMERATOR_ATTRIBUTES		// N4266
#  endif
#  if defined(__cpp_nested_namespace_definitions) && (__cpp_nested_namespace_definitions >= 201411)
#    define HAMON_HAS_CXX17_NESTED_NAMESPACE_DEFINITIONS	// N4230
#  endif
#  if defined(__cpp_inheriting_constructors) && (__cpp_inheriting_constructors >= 201511)
#    define HAMON_HAS_CXX17_INHERITING_CONSTRUCTORS	// P0136R1
#  endif
#  if defined(__cpp_variadic_using) && (__cpp_variadic_using >= 201611)
#    define HAMON_HAS_CXX17_VARIADIC_USING				// P0195R2
#  endif
#  if (HAMON_HAS_CPP_ATTRIBUTE(fallthrough) >= 201603)
#    define HAMON_HAS_CXX17_FALLTHROUGH				// P0188R1
#  endif
#  if (HAMON_HAS_CPP_ATTRIBUTE(nodiscard) >= 201603)
#    define HAMON_HAS_CXX17_NODISCARD					// P0189R1
#  endif
#  if (HAMON_HAS_CPP_ATTRIBUTE(maybe_unused) >= 201603)
#    define HAMON_HAS_CXX17_MAYBE_UNUSED				// P0212R1
#  endif
#  if (HAMON_CLANG_VERSION >= 30900)
#    define HAMON_HAS_CXX17_USING_ATTRIBUTE_NAMESPACES	// P0028R4
#  endif
#  if (HAMON_CXX_STANDARD >= 17)
#    define HAMON_HAS_CXX17_IGNORING_UNRECOGNIZED_ATTRIBUTES	// P0283R2
#  endif
#  if defined(__cpp_structured_bindings) && (__cpp_structured_bindings >= 201606)
#    define HAMON_HAS_CXX17_STRUCTURED_BINDINGS		// P0217R3
#  endif
#  if defined(__cpp_aggregate_bases) && (__cpp_aggregate_bases >= 201603)
#    define HAMON_HAS_CXX17_AGGREGATE_BASES			// P0017R1
#  endif
#  if (HAMON_CLANG_VERSION >= 30900)
#    define HAMON_HAS_CXX17_INIT_ENUM_CLASS			// P0138R2
#  endif
#  if (HAMON_CLANG_VERSION >= 30500)
#    define HAMON_HAS_CXX17_TEMPLATE_TEMPLATE_TYPENAME	// N4051
#  endif
#  if defined(__cpp_nontype_template_args) && (__cpp_nontype_template_args >= 201411)
#    define HAMON_HAS_CXX17_NONTYPE_TEMPLATE_ARGS		// N4268
#  endif
#  if defined(__cpp_template_template_args) && (__cpp_template_template_args >= 201611)
#    define HAMON_HAS_CXX17_TEMPLATE_TEMPLATE_ARGS		// P0522R0
#  endif
#  if (HAMON_CLANG_VERSION >= 40000)
#    define HAMON_HAS_CXX17_EXCEPTION_SPECIFICATIONS	// P0003R5
#  endif
#  if !defined(__has_include)
#    define HAMON_HAS_CXX17_HAS_INCLUDE				// P0061R1
#  endif
#endif

#if (HAMON_CLANG_VERSION >= 30800)
#  define HAMON_HAS_CXX17_AUTO_DEDUCTION_BRACED_INIT_LIST	// N3922
#endif

// C++20
#if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX20_FEATURE_TEST_MACROS								// P0941R2
#  define HAMON_HAS_CXX20_STRONGER_UNICODE_REQUIREMENTS						// P1041R4 P1139R2
#  if (HAMON_CLANG_VERSION >= 60000)
#    define HAMON_HAS_CXX20_BITFIELD_DEFAULT_MEMBER_INITIALIZER				// P0683R1
#    define HAMON_HAS_CXX20_CONST_QUALIFIED_POINTERS_TO_MEMBERS				// P0704R1
#    define HAMON_HAS_CXX20_CAPTURE_COPY_THIS								// P0409R2
#  endif
#  if (HAMON_CLANG_VERSION >= 70000)
#    if defined(__cpp_char8_t) && (__cpp_char8_t >= 201811)
#      define HAMON_HAS_CXX20_CHAR8_T										// P0482R6
#    endif
#  endif
#  if (HAMON_CLANG_VERSION >= 80000)
#    define HAMON_HAS_CXX20_RANGE_BASED_FOR_INITIALIZER						// P0614R1
#    define HAMON_HAS_CXX20_DEFAULT_CONSTRUCTIBLE_AND_ASSIGNABLE_STATELESS_LAMBDAS	// P0624R2
#    define HAMON_HAS_CXX20_CONSTEXPR_TRY_CATCH								// P1002R1
#    define HAMON_HAS_CXX20_NESTED_INLINE_NAMESPACES						// P1094R2
#    define HAMON_HAS_CXX20_CONST_MISMATCH_WITH_DEFAULTED_COPY_CONSTRUCTOR	// P0641R2
#    define HAMON_HAS_CXX20_PROHIBIT_AGGREGATES_WITH_USER_DECLARED_CONSTRUCTORS	// P1008R1
#  if defined(__cpp_constexpr_in_decltype) && (__cpp_constexpr_in_decltype >= 201711)
#    define HAMON_HAS_CXX20_CONSTEXPR_IN_DECLTYPE							// P0859R0
#  endif
#  endif
#  if (HAMON_CLANG_VERSION >= 90000)
#    define HAMON_HAS_CXX20_TWOS_COMPLEMENT_SIGNED_INTEGERS					// P1236R1
#    define HAMON_HAS_CXX20_VA_OPT											// P0306R4 P1042R1
#    define HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED							// P0595R2
#    define HAMON_HAS_CXX20_DEPRECATE_COMMA_IN_SUBSCRIPTING_EXPRESSIONS		// P1161R3
#    define HAMON_HAS_CXX20_ADL_AND_FUNCTION_TEMPLATES						// P0846R0
#    define HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_CAST							// P1327R1
#    if defined(__cpp_generic_lambdas) && (__cpp_generic_lambdas >= 201707)
#      define HAMON_HAS_CXX20_GENERIC_LAMBDAS								// P0428R2
#    endif
#    if defined(__cpp_init_captures) && (__cpp_init_captures >= 201803)
#      define HAMON_HAS_CXX20_INIT_CAPTURES									// P0780R2
#    endif
#    if defined(__cpp_impl_destroying_delete) && (__cpp_impl_destroying_delete >= 201806)
#      define HAMON_HAS_CXX20_DESTROYING_DELETE								// P0722R3
#    endif
#    if (HAMON_HAS_CPP_ATTRIBUTE(nodiscard) >= 201907)
#      define HAMON_HAS_CXX20_NODISCARD_WITH_MESSAGE						// P1301R4
#      define HAMON_HAS_CXX20_NODISCARD_CTOR								// P1771R1
#    endif
#    if (HAMON_HAS_CPP_ATTRIBUTE(no_unique_address) >= 201803)
#      define HAMON_HAS_CXX20_NO_UNIQUE_ADDRESS								// P0840R2
#    endif
#    if defined(__cpp_conditional_explicit) && (__cpp_conditional_explicit >= 201806)
#      define HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT							// P0892R2
#    endif
#  endif
#  if (HAMON_CLANG_VERSION >= 100000)
#    define HAMON_HAS_CXX20_ABBREVIATED_FUNCTION_TEMPLATE					// P1141R2
#    define HAMON_HAS_CXX20_DEPRECATE_VOLATILE								// P1152R4
#    if defined(__cpp_designated_initializers) && (__cpp_designated_initializers >= 201707)
#      define HAMON_HAS_CXX20_DESIGNATED_INITIALIZERS						// P0329R4
#    endif
#    if defined(__cpp_constinit) && (__cpp_constinit >= 201907)
#      define HAMON_HAS_CXX20_CONSTINIT										// P1143R2
#    endif
#  endif
#  if (HAMON_CLANG_VERSION >= 120000)
#    define HAMON_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_CLASS				// P0732R2
#    if defined(__cpp_nontype_template_args) && (__cpp_nontype_template_args >= 201911)
#      define HAMON_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_FLOAT				// P1907R1
#    endif
#    if (HAMON_HAS_CPP_ATTRIBUTE(likely) >= 201803)
#      define HAMON_HAS_CXX20_LIKELY										// P0479R5
#    endif
#    if (HAMON_HAS_CPP_ATTRIBUTE(unlikely) >= 201803)
#      define HAMON_HAS_CXX20_UNLIKELY										// P0479R5
#    endif
#    if defined(__cpp_constexpr_dynamic_alloc) && (__cpp_constexpr_dynamic_alloc >= 201907)
#      define HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC						// P0784R7
#    endif
#  endif
#  if defined(__cpp_impl_three_way_comparison) && (__cpp_impl_three_way_comparison >= 201711L)
#    define HAMON_HAS_CXX20_THREE_WAY_COMPARISON							// P0515R3 P1185R2 P1186R3 P1630R1
#  endif
#  if defined(__cpp_constexpr) && (__cpp_constexpr >= 201907)
#    define HAMON_HAS_CXX20_CONSTEXPR										// P1064R0 P1002R1 P1327R0 P1330R0 P1331R2 P1668R1
#  endif
#  if defined(__cpp_concepts) && (__cpp_concepts >= 201907)
#    define HAMON_HAS_CXX20_CONCEPTS										// P0734R0
#  endif
#  if defined(__cpp_impl_coroutine) && (__cpp_impl_coroutine >= 201902)
#    define HAMON_HAS_CXX20_COROUTINES										// P0912R5
#  endif
#  if defined(__cpp_consteval) && (__cpp_consteval >= 201811)
#    define HAMON_HAS_CXX20_CONSTEVAL										// P1073R3
#  endif
#  if defined(__cpp_deduction_guides) && (__cpp_deduction_guides >= 201907)
#    define HAMON_HAS_CXX20_DEDUCTION_GUIDES								// P1021R4 P1816R0 P1814R0
#  endif
#  if defined(__cpp_using_enum) && (__cpp_using_enum >= 201907)
#    define HAMON_HAS_CXX20_USING_ENUM										// P1099R5
#  endif
#  if defined(__cpp_aggregate_paren_init) && (__cpp_aggregate_paren_init >= 201902)
#    define HAMON_HAS_CXX20_AGGREGATE_PAREN_INIT							// P0960R3
#  endif
#  if defined(__cpp_modules) && (__cpp_modules >= 201907)
#    define HAMON_HAS_CXX20_MODULES											// P1103R3
#  endif

//#  define HAMON_HAS_CXX20_DEPRECATE_IMPLICIT_CAPTURE_COPY_THIS			// P0806R2
//#  define HAMON_HAS_CXX20_STRUCTURED_BINDING_EXTENSIONS					// P1091R3,P1381R1
//#  define HAMON_HAS_CXX20_ACCESS_CHECKING_ON_SPECIALIZATIONS				// P0692R1
//#  define HAMON_HAS_CXX20_CONVERSIONS_TO_UNBOUNDED_ARRAY					// P0388R4
//#  define HAMON_HAS_CXX20_LAMBDAS_IN_UNEVALUATED_CONTEXTS					// P0315R4
//#  define HAMON_HAS_CXX20_OPTIONAL_TYPENAME								// P0634R3
//#  define HAMON_HAS_CXX20_CONDITIONALLY_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS	// P0848R3

#endif	// C++20

#if (HAMON_CLANG_VERSION >= 60000)
#  if (HAMON_CXX_STANDARD >= 17)	// Defect report としてC++17に適用される
#    define HAMON_HAS_CXX20_INITIALIZER_LIST_CTAD							// P0702R1
#  endif
#endif
#if (HAMON_CLANG_VERSION >= 80000)
#  define HAMON_HAS_CXX20_RELAXING_STRUCTURED_BINDINGS						// P0961R1
#  define HAMON_HAS_CXX20_RELAXING_RANGE_FOR								// P0962R1
#  define HAMON_HAS_CXX20_STRUCTURED_BINDINGS_TO_ACCESSIBLE_MEMBERS			// P0969R0
#endif
#if (HAMON_CLANG_VERSION >= 90000)
#  define HAMON_HAS_CXX20_ARRAY_SIZE_DEDUCTION_NEW							// P1009R2
#  define HAMON_HAS_CXX20_EXCEPTION_SPEC_DEFAULTED_FUNCTION					// P1286R2
#endif
#if (HAMON_CLANG_VERSION >= 110000)
#  define HAMON_HAS_CXX20_POINTER_TO_BOOL_CONVERTING						// P1957R2
#  define HAMON_HAS_CXX20_PSEUDO_DESTRUCTOR									// P0593R6
#endif
#if (HAMON_CLANG_VERSION >= 130000)
#  define HAMON_HAS_CXX20_IMPLICIT_MOVE										// P1825R0
#endif

//#  define HAMON_HAS_CXX20_SIMPLIFYING_IMPLICIT_LAMBDA_CAPTURE				// P0588R1

#endif // HAMON_CONFIG_COMPILER_CLANG_HPP
