/** Copyright (C) 2023 Muqiu Han <muqiu-han@outlook.com> */

#ifndef SINBUGER_RESULT_H
#define SINBUGER_RESULT_H

#include <iostream>
#include <optional>
#include <variant>

template <typename T> struct Ok;
template <typename E> struct Err;
struct Void
{
};

// Result is a type that represents either success (Ok) or failure (Err).
template <typename T, typename E> struct Result
{

  std::variant<Ok<T>, Err<E>> value;

  Result() {}
  Result(const Ok<T> & val)
    : value(val)
  {
  }
  Result(const Err<E> & val)
    : value(val)
  {
  }

  friend std::ostream &
  operator<<(std::ostream & os, const Result & r)
  {
    if (r.is_ok())
      os << r.unwrap();
    else
      os << r.unwrap_err();
    return os;
  }

  Result
  operator=(Ok<T> val)
  {
    value = val;
    return *this;
  }

  Result
  operator=(Err<E> val)
  {
    value = val;
    return *this;
  }

  bool
  operator==(const Ok<T> & val) const
  {
    return is_ok() && unwrap() == val.value;
  }

  bool
  operator==(const Err<E> & val) const
  {
    return is_err() && unwrap_err() == val.value;
  }

  bool
  operator==(const Result<T, E> & rhs) const
  {
    return ((is_ok() && rhs.is_ok() && unwrap() == rhs.unwrap())
            || (is_err() && rhs.is_err() && unwrap_err() == rhs.unwrap_err()));
  }

  bool
  operator!=(const Result<T, E> & rhs) const
  {
    return !(*this == rhs);
  }

  // Returns true if the result is Ok.
  bool
  is_ok() const
  {
    return std::holds_alternative<Ok<T>>(value);
  }

  // Returns true if the result is Err.
  bool
  is_err() const
  {
    return std::holds_alternative<Err<E>>(value);
  }

  // Converts from Result<T, E> to std::optional<T>.
  std::optional<T>
  ok() const
  {
    if (is_ok())
      return std::get<0>(value).value;
    return {};
  }

  // Converts from Result<T, E> to std::optional<E>.
  std::optional<E>
  err() const
  {
    if (is_err())
      return std::get<1>(value).value;
    return {};
  }

  // Returns res if the result is Ok, otherwise returns the Err value of self.
  template <typename U>
  Result<U, E>
  and_(const Result<U, E> & res)
  {
    if (is_ok())
      return res;
    return Err(err().value());
  }

  // Synonymous with Result.and_(res)
  template <typename U>
  Result<U, E>
  operator&&(const Result<U, E> & res)
  {
    if (is_ok())
      return res;
    return Err(err().value());
  }

  // Calls op if the result is Ok, otherwise returns the Err value of self.
  // This function can be used for control flow based on Result values.
  template <typename Function>
  Result
  and_then(Function op)
  {
    if (is_ok())
      return op(unwrap());
    return Err(err().value());
  }

  // Returns res if the result is Err,
  // otherwise returns the Ok value of self.
  Result
  or_(const Result & res)
  {
    if (is_err())
      return res;
    return Ok(ok().value());
  }

  // Synonymous with Result.or_(res)
  Result
  operator||(const Result & res)
  {
    if (is_err())
      return res;
    return Ok(ok().value());
  }

  // Calls op if the result is Err,
  // otherwise returns the Ok value of self.
  template <typename Function>
  Result
  or_else(Function op)
  {
    if (is_err())
      return op(unwrap_err());
    return Ok(ok().value());
  }

  // Unwraps a result, yielding the content of an Ok. Else, it returns optb.
  T
  unwrap_or(T optb)
  {
    if (is_ok())
      return unwrap();
    return optb;
  }

  // Unwraps a result, yielding the content of an Ok.
  // If the value is an Err then it calls op with its value.
  template <typename Function>
  T
  unwrap_or_else(Function op)
  {
    if (is_ok())
      return unwrap();
    return op(unwrap_err());
  }

  bool
  contains(const T & this_value)
  {
    return is_ok() ? unwrap() == this_value : false;
  }

  bool
  contains_err(const E & this_value)
  {
    return is_err() ? unwrap_err() == this_value : false;
  }

  // Maps a Result<T, E> to Result<U, E> by
  // applying a function to a contained Ok value,
  // leaving an Err value untouched.
  //
  // This function can be used to compose the results of two functions.
  template <typename Function>
  auto
  map(Function fn) -> Result<decltype(fn(T())), E>
  {
    if (is_ok())
      return Result<decltype(fn(T())), E>(Ok<decltype(fn(T()))>(fn(unwrap())));
    else
      return Result<decltype(fn(T())), E>(Err<E>(unwrap_err()));
  }

  // Applies a function to the contained value (if any),
  // or returns the provided default (if not).
  template <typename Value, typename Function>
  auto
  map_or(Value default_value, Function fn) -> decltype(fn(T()))
  {
    if (is_ok())
      return fn(unwrap());
    else
      return default_value;
  }

  // Maps a Result<T, E> to U by applying a function to a contained Ok value,
  // or a fallback function to a contained Err value.
  //
  // This function can be used to unpack a successful result while handling an
  // error.
  template <typename ErrorFunction, typename OkFunction>
  auto
  map_or_else(ErrorFunction err_fn, OkFunction ok_fn) -> decltype(ok_fn(T()))
  {
    if (is_ok())
      return ok_fn(unwrap());
    else
      return err_fn(unwrap_err());
  }

  // Maps a Result<T, E> to Result<T, F> by
  // applying a function to a contained Err value,
  // leaving an Ok value untouched.
  //
  // This function can be used to pass
  // through a successful result while handling an error.
  template <typename Function>
  auto
  map_err(Function fn) -> Result<T, decltype(fn(E()))>
  {
    if (is_err())
      return Result<T, decltype(fn(E()))>(Err<decltype(fn(E()))>(fn(unwrap_err())));
    else
      return Result<T, decltype(fn(E()))>(Ok<T>(unwrap()));
  }

  // Unwraps a result, yielding the content of an Ok.
  // Throws if the value is an Err
  auto
  unwrap() const
  {
    if (is_ok())
      return ok().value();
    else
      throw err().value();
  }

  // Unwraps a result, yielding the content of an Ok.
  // Throws if the value is an Err with the `msg` argument
  T
  expect(const std::string & msg)
  {
    if (is_ok())
      return unwrap();
    if constexpr (std::is_same_v<E, std::string>)
      throw msg + ": " + unwrap_err();
    else
      throw msg + ": " + std::to_string(unwrap_err());
  }

  // Unwraps a result, yielding the content of an Err.
  // Throws if the value is an Ok,
  auto
  unwrap_err() const
  {
    if (is_err())
      return err().value();
    else
      throw ok().value();
  }

  // Unwraps a result, yielding the content of an Err.
  // Throws if the value is an Ok with the `msg` argument
  E
  expect_err(const std::string & msg)
  {
    if (is_err())
      return unwrap_err();
    if constexpr (std::is_same_v<T, std::string>)
      throw msg + ": " + unwrap();
    else
      throw msg + ": " + std::to_string(unwrap());
  }

  // Returns the contained value or a default
  // if Ok, returns the contained value,
  // otherwise if Err, returns the default value for that type.
  T
  unwrap_or_default() const
  {
    if (is_ok())
      return unwrap();
    else
      return T();
  }
};

template <typename T> struct Ok
{
  T value;
  Ok(T value)
    : value(value)
  {
  }

  template <typename Function>
  Result<T, T>
  and_then(Function op)
  {
    return Result<T, T>(*this).and_then(op);
  }
};

template <typename E> struct Err
{
  E value;
  Err(E value)
    : value(value)
  {
  }

  template <typename Function>
  Result<E, E>
  and_then(Function op)
  {
    return Result<E, E>(*this).and_then(op);
  }
};

#endif /* sinbuger_RESULT_H */
