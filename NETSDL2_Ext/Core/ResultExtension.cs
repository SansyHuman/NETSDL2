using System;
using System.Collections.Generic;
using System.Linq;
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
        public static Result<U, F> Map<S, F, U>(this Result<S, F> obj, Func<S, U> f)
        {
            if (obj.IsSuccess)
                return Result<U, F>.MakeResult(f(obj.ResultValue));

            return Result<U, F>.MakeFailure(obj.ErrorValue);
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
        public static U MapOrElse<S, F, U>(this Result<S, F> obj, Func<F, U> defaultFunc, Func<S, U> f)
        {
            if (obj.IsFailure)
                return defaultFunc(obj.ErrorValue);

            return f(obj.ResultValue);
        }
    }
}
