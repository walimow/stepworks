#include <list>
#include <optional>

#include <reposition.hpp>
#include "gtest/gtest.h"
#include <rw/rforward.hpp>

using FW = stepworks::fw<int, std::list, std::optional>;

TEST (reposition_test_case, supp_true){
    auto is_t = stepworks::has_reposition<FW>::value;
    EXPECT_TRUE(is_t);
}
