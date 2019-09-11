#pragma once

///  sample from stackoverflow
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

namespace stepworks{

    template<class T>
    struct default_copier {
      T* operator()(T const* tin)const {
        if (!tin) return nullptr;
        return new T(*tin);
      }
      void* operator()(void* dest, T const* tin)const {
        if (!tin) return nullptr;
        return new(dest) T(*tin);
      }
    };
    
    template<class T, class Copier=default_copier<T>, class Deleter=std::default_delete<T>,
      class Base=std::unique_ptr<T, Deleter>
    >
    struct value_ptr:Base, private Copier {
      using Base::Base;
      value_ptr() = default;

      value_ptr( Base b, Copier c={} ):
        Base(std::move(b)),
        Copier(std::move(c))
      {}

      Copier const& get_copier() const {
        return *this;
      }

      value_ptr clone() const {
        return {
          Base(
            get_copier()(this->get()),
            this->get_deleter()
          ),
          get_copier()
        };
      }
      value_ptr(value_ptr&&)=default;
      value_ptr& operator=(value_ptr&&)=default;

      value_ptr(value_ptr const& o):value_ptr(o.clone()) {}
      value_ptr& operator=(value_ptr const&o) {
        if (o && *this) {
          // if we are both non-null, assign contents:
          **this = *o;
        } else {
          // otherwise, assign a clone (which could itself be null):
          *this = o.clone();
        }
        return *this;
      }
    };
    template<class T, class...Args>
    value_ptr<T> make_value_ptr( Args&&... args ) {
      return {std::make_unique<T>(std::forward<Args>(args)...)};
    }
    
    struct noisy {
        noisy() { std::cout << "ctor\n"; }
        ~noisy() { std::cout << "dtor\n"; }
        noisy(noisy&&) { std::cout << "ctor&&\n"; }
        noisy(noisy const&) { std::cout << "ctor const&\n"; }
        noisy& operator=(noisy&&) { std::cout << "=&&\n"; return *this; }
        noisy& operator=(noisy const&) { std::cout << "=const&\n"; return *this; }
    };

}    
