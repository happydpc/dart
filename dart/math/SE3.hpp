/*
 * Copyright (c) 2016, Graphics Lab, Georgia Tech Research Corporation
 * Copyright (c) 2016, Humanoid Lab, Georgia Tech Research Corporation
 * Copyright (c) 2016, Personal Robotics Lab, Carnegie Mellon University
 * All rights reserved.
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DART_MATH_SE3_HPP_
#define DART_MATH_SE3_HPP_

#include <Eigen/Eigen>

#include "dart/math/MathTypes.hpp"
#include "dart/math/Geometry.hpp"
#include "dart/math/SE3Base.hpp"

namespace dart {
namespace math {

//struct RotationMatrixRep : SE3Representation {};

template <typename S_, typename Rep> // TODO(JS): Rename Rep to RotRep
class SE3 : public SE3Base<SE3<S_, Rep>>
{
public:

  using This = SE3<S_, Rep>;
  using Base = SE3Base<This>;

  using S = typename Base::S;

  using SO3Type = typename Base::SO3Type;
  using TranslationType = typename Base::TranslationType;

  using Tangent = typename Base::Tangent;
  using se3 = typename Base::se3;

  using Base::operator =;
  using Base::operator *;
  using Base::operator *=;

  using Base::coordinates;
  using Base::matrix;

  SE3() : Base(), mRotation(SO3Type()), mTranslation(TranslationType())
  {
    // Do nothing
  }

  SE3(const SE3& other)
    : Base(),
      mRotation(other.mRotation),
      mTranslation(other.mTranslation)
  {
    // Do nothing
  }

  SE3(SE3&& other)
    : Base(),
      mRotation(std::move(other.mRotation)),
      mTranslation(std::move(other.mTranslation))
  {
    // Do nothing
  }

//  template <typename Derived>
//  SE3(const SE3Base<Derived>& other)
//    : mRepData(detail::SE3::convert_impl<S, typename Derived::Rep, Rep>::run(
//              other.derived().matrix()))
//  {
//    // Do nothing
//  }

//  template <typename Derived>
//  explicit SE3(const Eigen::MatrixBase<Derived>& matrix) : mRepData(matrix)
//  {
//    using namespace Eigen;
//    EIGEN_STATIC_ASSERT_SAME_MATRIX_SIZE(Derived, RepDataType)
//  }

//  template <typename Derived>
//  explicit SE3(Eigen::MatrixBase<Derived>&& matrix) : mRepData(std::move(matrix))
//  {
//    using namespace Eigen;
//    EIGEN_STATIC_ASSERT_SAME_MATRIX_SIZE(Derived, RepDataType)
//  }

//  explicit SE3(const SE3& tangent) : mRepData(expMapRot(tangent))
//  {
//    // Do nothing
//  }

//  explicit SE3(SE3&& tangent) : mRepData(expMapRot(std::move(tangent)))
//  {
//    // Do nothing
//  }

  SE3& operator=(const SE3& other)
  {
    Base::operator =(other);
    return *this;
  }

  SE3& operator=(SE3&& other)
  {
    Base::operator=(std::move(other));
    return *this;
  }

  bool operator ==(const SE3& other)
  {
    return (mRotation == other.mRotation)
        && (mTranslation == other.mTranslation);
  }

  void setIdentity()
  {
    mRotation.setIdentity();
    mTranslation.setZero();
  }

  void setRandom()
  {
    mRotation.setRandom();
    mTranslation.setRandom();
  }

  void inverse()
  {
    mRotation.inverse();
    mTranslation = -(mRotation * mTranslation);
  }

  const SE3 inversed() const
  {
    SO3Type inversed = mRotation.inversed();

    return SE3(inversed, -(inversed * mTranslation));
  }

//  static SE3 exp(const SE3& tangent)
//  {
//    return SE3(expMapRot(tangent));
//    // TODO(JS): improve
//  }

//  static SE3 log(const This& point)
//  {
//    return ::dart::math::logMap(point.mRepData);
//    // TODO(JS): improve
//  }

//  /// \returns A pointer to the data array of internal data type
//  S* data()
//  {
//    return mRepData.data();
//  }

protected:

  template <typename>
  friend class SE3Base;

//  RepDataType mRepData;
  SO3<S, Rep> mRotation;
  Eigen::Matrix<S, 3, 1> mTranslation;
};

} // namespace math
} // namespace dart

#endif // DART_MATH_SE3_HPP_
