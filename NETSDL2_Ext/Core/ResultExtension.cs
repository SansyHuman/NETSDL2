using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace NETSDL2.Core
{
    /// <summary>
    /// Extensions of <see cref="Result{Success, Failure}"/>.
    /// </summary>
    public static class ResultExtension
    {
        /// <summary>
        /// Check whether the result is success with specific value.
        /// </summary>
        /// <typeparam name="S">Success value type.</typeparam>
        /// <typeparam name="F">Error value type.</typeparam>
        /// <param name="obj"></param>
        /// <param name="val">Value that the success result should have.</param>
        /// <param name="comparer">Comparer to used comparing success value.</param>
        /// <returns><see langword="true"/> if the result is success with the <paramref name="val"/>,
        /// else <see langword="false"/>.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static bool Contains<S, F>(this Result<S, F> obj, S val, IEqualityComparer<S> comparer)
        {
            return obj.IsSuccess && comparer.Equals(obj.ResultValue, val);
        }

        /// <summary>
        /// Check whether the result is success with specific value.
        /// </summary>
        /// <typeparam name="S">Success value type.</typeparam>
        /// <typeparam name="F">Error value type.</typeparam>
        /// <param name="obj"></param>
        /// <param name="val">Value that the success result should have.</param>
        /// <returns><see langword="true"/> if the result is success with the <paramref name="val"/>,
        /// else <see langword="false"/>.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static bool Contains<S, F>(this Result<S, F> obj, S val) where S : IEquatable<S>
        {
            return obj.IsSuccess && val.Equals(obj.ResultValue);
        }

        /// <summary>
        /// Check whether the result is failure with specific value.
        /// </summary>
        /// <typeparam name="S">Success value type.</typeparam>
        /// <typeparam name="F">Error value type.</typeparam>
        /// <param name="obj"></param>
        /// <param name="val">Value that the failure result should have.</param>
        /// <param name="comparer">Comparer to used comparing failure value.</param>
        /// <returns><see langword="true"/> if the result is failure with the <paramref name="val"/>,
        /// else <see langword="false"/>.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static bool ContainsErr<S, F>(this Result<S, F> obj, F val, IEqualityComparer<F> comparer)
        {
            return obj.IsFailure && comparer.Equals(obj.ErrorValue, val);
        }

        /// <summary>
        /// Check whether the result is failure with specific value.
        /// </summary>
        /// <typeparam name="S">Success value type.</typeparam>
        /// <typeparam name="F">Error value type.</typeparam>
        /// <param name="obj"></param>
        /// <param name="val">Value that the failure result should have.</param>
        /// <returns><see langword="true"/> if the result is failure with the <paramref name="val"/>,
        /// else <see langword="false"/>.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static bool ContainsErr<S, F>(this Result<S, F> obj, F val) where F : IEquatable<F>
        {
            return obj.IsFailure && val.Equals(obj.ErrorValue);
        }

        /// <summary>
        /// Call the provided closure with the contained value if success.
        /// </summary>
        /// <typeparam name="S">Success value type.</typeparam>
        /// <typeparam name="F">Error value type.</typeparam>
        /// <param name="obj"></param>
        /// <param name="f">Closure to call on success.</param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void Inspect<S, F>(this Result<S, F> obj, Action<S> f)
        {
            if (obj.IsSuccess)
                f(obj.ResultValue);
        }

        /// <summary>
        /// Call the provided closure with the contained error value if failure.
        /// </summary>
        /// <typeparam name="S">Success value type.</typeparam>
        /// <typeparam name="F">Error value type.</typeparam>
        /// <param name="obj"></param>
        /// <param name="f">Closure to call on failure.</param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void InspectErr<S, F>(this Result<S, F> obj, Action<F> f)
        {
            if (obj.IsFailure)
                f(obj.ErrorValue);
        }

        /// <summary>
        /// Get whether the result is failure and the value inside of it matches a predicate.
        /// </summary>
        /// <typeparam name="S">Success value type.</typeparam>
        /// <typeparam name="F">Error value type.</typeparam>
        /// <param name="obj"></param>
        /// <param name="f">Predicate to test error value.</param>
        /// <returns><see langword="true"/> if the result is failure and the value inside of it matches a predicate.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static bool IsFailureAnd<S, F>(this Result<S, F> obj, Predicate<F> f)
        {
            return obj.IsFailure && f(obj.ErrorValue);
        }

        /// <summary>
        /// Get whether the result is success and the value inside of it matches a predicate.
        /// </summary>
        /// <typeparam name="S">Success value type.</typeparam>
        /// <typeparam name="F">Error value type.</typeparam>
        /// <param name="obj"></param>
        /// <param name="f">Predicate to test result value.</param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static bool IsSuccessAnd<S, F>(this Result<S, F> obj, Predicate<S> f)
        {
            return obj.IsSuccess && f(obj.ResultValue);
        }

        /// <summary>
        /// Map a <see cref="Result{S, F}"/> to <see cref="Result{U, F}"/> by applying a function to a
        /// contained result value, leaving an error value untouched.
        /// </summary>
        /// <typeparam name="S">Success value type.</typeparam>
        /// <typeparam name="F">Error value type.</typeparam>
        /// <typeparam name="U">New success value type.</typeparam>
        /// <param name="obj"></param>
        /// <param name="f">Function to cast <typeparamref name="S"/> to <typeparamref name="U"/>.</param>
        /// <returns>New <see cref="Result{U, F}"/>.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<U, F> Map<S, F, U>(this Result<S, F> obj, Func<S, U> f)
        {
            if (obj.IsSuccess)
                return Result<U, F>.MakeResult(f(obj.ResultValue));

            return Result<U, F>.MakeFailure(obj.ErrorValue);
        }

        /// <summary>
        /// Maps a <see cref="Result{S, F}"/> to <see cref="Result{S, E}"/> by applying a function to a
        /// contained error value, leaving a result value untouched.
        /// </summary>
        /// <typeparam name="S">Success value type.</typeparam>
        /// <typeparam name="F">Error value type.</typeparam>
        /// <typeparam name="E">New error value type.</typeparam>
        /// <param name="obj"></param>
        /// <param name="f">Function to cast <typeparamref name="F"/> to <typeparamref name="E"/>.</param>
        /// <returns>New <see cref="Result{S, E}"/>.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<S, E> MapErr<S, F, E>(this Result<S, F> obj, Func<F, E> f)
        {
            if (obj.IsFailure)
                return Result<S, E>.MakeFailure(f(obj.ErrorValue));

            return Result<S, E>.MakeResult(obj.ResultValue);
        }

        /// <summary>
        /// Returns the provided default (if failure), or applies a function to the contained value (if success).
        /// </summary>
        /// <typeparam name="S">Success value type.</typeparam>
        /// <typeparam name="F">Error value type.</typeparam>
        /// <typeparam name="U">New success value type.</typeparam>
        /// <param name="obj"></param>
        /// <param name="defaultValue">Default value on error.</param>
        /// <param name="f">Function to cast <typeparamref name="S"/> to <typeparamref name="U"/>.</param>
        /// <returns>Casted value on success or default value on error.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static U MapOr<S, F, U>(this Result<S, F> obj, U defaultValue, Func<S, U> f)
        {
            if (obj.IsFailure)
                return defaultValue;

            return f(obj.ResultValue);
        }

        /// <summary>
        /// Maps a <see cref="Result{S, F}"/> to <typeparamref name="U"/> by applying fallback function
        /// default to a contained error value, or function f to a contained result value.
        /// </summary>
        /// <typeparam name="S">Success value type.</typeparam>
        /// <typeparam name="F">Error value type.</typeparam>
        /// <typeparam name="U">New success value type.</typeparam>
        /// <param name="obj"></param>
        /// <param name="defaultFunc">Function to cast <typeparamref name="F"/> to <typeparamref name="U"/>.</param>
        /// <param name="f">Function to cast <typeparamref name="S"/> to <typeparamref name="U"/>.</param>
        /// <returns>Casted value.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static U MapOrElse<S, F, U>(this Result<S, F> obj, Func<F, U> defaultFunc, Func<S, U> f)
        {
            if (obj.IsFailure)
                return defaultFunc(obj.ErrorValue);

            return f(obj.ResultValue);
        }

        /// <summary>
        /// Returns the contained result value or a provided default.
        /// </summary>
        /// <typeparam name="S">Success value type.</typeparam>
        /// <typeparam name="F">Error value type.</typeparam>
        /// <param name="obj"></param>
        /// <param name="defaultValue">Default value if the result is failure.</param>
        /// <returns>The result value or default value on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static S GetResultOr<S, F>(this Result<S, F> obj, S defaultValue)
        {
            if (obj.IsFailure)
                return defaultValue;

            return obj.ResultValue;
        }

        /// <summary>
        /// Returns the contained result value or computes it from a closure.
        /// </summary>
        /// <typeparam name="S">Success value type.</typeparam>
        /// <typeparam name="F">Error value type.</typeparam>
        /// <param name="obj"></param>
        /// <param name="f">Closure to transform error value to result value.</param>
        /// <returns>The result value or result of closure on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static S GetResultOrElse<S, F>(this Result<S, F> obj, Func<F, S> f)
        {
            if (obj.IsFailure)
                return f(obj.ErrorValue);

            return obj.ResultValue;
        }
    }
}
