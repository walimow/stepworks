//
// Created by karsten on 20.12.20.
//

#include "gtest/gtest.h"
#include <util/log.hpp>
#include <cassert>

using stepworks::util::global_logging_support;
using stepworks::util::reset_global_logging;


TEST (logsupport_test_case, init_log) {

  EXPECT_DEBUG_DEATH( global_logging_support() .out( "should fail by assert"),"");
  ASSERT_TRUE( reset_global_logging() );
  global_logging_support().output(" Stepworks",  "logging: on") ;

}