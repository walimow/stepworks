//
// Created by karsten on 16.01.21.
//

#pragma once

namespace stepworks::util::call {

#define CALL_MEMBER_FN(object, ptrToMember)  ((object).*(ptrToMember))

}