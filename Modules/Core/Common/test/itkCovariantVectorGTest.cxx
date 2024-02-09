/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

// First include the header file to be tested:
#include "itkCovariantVector.h"
#include <gtest/gtest.h>


// Tests that a CovariantVector that is "value-initialized" (by empty braces, `{}`) is zero-filled.
TEST(CovariantVector, ValueInitializedIsZeroFilled)
{
  const auto expectZeroFilled = [](const auto & fixedArray) {
    for (const auto element : fixedArray)
    {
      EXPECT_EQ(element, 0);
    }
  };

  expectZeroFilled(itk::CovariantVector<int>{});
  expectZeroFilled(itk::CovariantVector<float, 2>{});
  expectZeroFilled(itk::CovariantVector<double, 4>{});
}
