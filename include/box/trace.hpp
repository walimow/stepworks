//
// Created by karsten on 26.11.20.
//

#ifndef BOX_TRACE_HPP
#define BOX_TRACE_HPP

#include "apply.hpp"
#include <iostream>
#include "def.hpp"
#include "util.hpp"
//#include "singular.hpp"
#include "wrekurs.hpp"

namespace stepworks::bxx::util {


    template<typename Ty, template<typename ...> typename Aggregate>
    struct stream_box {
        struct data_t {
            const stream_box& _src_fo;

            const std::string pre_text = " ";
            const std::string post_text = " ";
            stepworks::bxx::ref_wrapper<std::ostream> _r{std::cout};

            int level = 0;
       //     unsigned int _count = 0;
            unsigned int _total = 0;

            data_t(const data_t&)=delete;
           data_t(data_t&&)noexcept=default;
          explicit  data_t(const stream_box& o, const std::string&b, const std::string&a)
          :   _src_fo(o),  pre_text (b),   post_text(a)        {
            }
         explicit data_t()=delete;

          data_t& operator=(data_t&&) =default;
          data_t& operator=(const data_t&) =delete;
        };

        using value_t = data_t;

        auto mk_data_instance(const std::string& pre="",const std::string &post=""){
            return data_t{*this, pre,post};
        }

        using fpre_aggregate = data_t (*)(data_t , const typename box<Ty, Aggregate>::agg_t &);
        fpre_aggregate _fpre;

        using fpost_aggregate = data_t (*)(data_t , const typename box<Ty, Aggregate>::agg_t &);
        fpost_aggregate _fpost;


        auto wpre_text(const data_t&&d) const {
            d._r._ref<<d.pre_text;
      //      return std::move(d);
      //      return std::forward<const data_t>(  (data_t&&) d);
            return data_t( const_cast<data_t&&> (d) );

        }


        auto wpost_text( data_t&&d)const {
            d._r._ref<<d.post_text;
            return std::forward<data_t&&>(d);
        }


        auto wpost_a(const Ty&a,data_t&&d)const {
            d._r._ref<<a;
            return std::forward< data_t&&>(d);
       //     return std::move(d);
        }

        auto operator()(const Ty &a,  const data_t&& d) const {
         //   d._count++;
         //todooooo   d._total++;
            return  wpost_text( wpost_a( a, wpre_text(std::move(d))) );
        }

        auto perform_pre(const typename  box<Ty,Aggregate>::agg_t  &a, const data_t&& d) const {
            return _fpre ? _fpre(a, std::move(d)) : std::move(d);
        }

        auto perform_post(const typename  box<Ty,Aggregate>::agg_t  &a, const data_t&& d) const {
            return _fpost ? _fpost(a, std::move(d)) : std::move(d);
        }

        auto perform_agg(const typename  box<Ty,Aggregate>::agg_t &a, const data_t&& d) const {
            return stepworks::iterativ_continuation(*this, a, std::move(d)   );
        }



        auto perform_choice(const typename  box<Ty,Aggregate>::type &a, const data_t&& d) const
                {
                        const auto& o= d._src_fo;
                       auto test_ = a.index();   std::cout<<"--->"<<test_<<"<---\n";
                       assert(test_ <=1);
                        return   a.index()==0  ?
                        o(  std::get< Ty >(a) , std::forward<const data_t&&>(d) )
                        :
                        o(  std::get< typename box<Ty,Aggregate>::agg_t >(a) , std::forward<const data_t&&>(d) );
                };

        auto operator()(const typename box<Ty,Aggregate>::agg_t  &a, data_t&& d) const->data_t {
            return  perform_post(a,  perform_agg( a,    perform_pre(a, std::move(d))));
        }

        auto operator()(const typename box<Ty,Aggregate>::type &a, const data_t&& d) const->const stream_box::data_t;

        data_t pre_aggregate(const typename box<Ty, Aggregate>::agg_t &a, data_t&& d) const {

            d.level++;
        //    d._count=0;
            if (_fpre)
               d=  std::move( _fpre(std::move(d), a));
            else
                return std::move(d);
        }

        data_t post_aggregate(const typename box<Ty, Aggregate>::agg_t &a, data_t&& d) const {
            d.level--;
            if (_fpost)
                return _fpost(std::move(d), a);
            else
                return std::move(d);
        }
    };


    template<typename Ty, template <typename...>typename Aggregate>
    auto stream_box <Ty, Aggregate>
    ::operator()(const typename box<Ty, Aggregate>::type &a, const stream_box::data_t&& d) const ->const stream_box::data_t{
std::cout<<"-!- "<< a.index()<<".\t";
  //     auto t = a.index();
        return  perform_choice(a, std::move(d));
    }


    template<typename Ty, template<typename ...> typename Aggregate,
            typename W=stream_box<Ty, Aggregate>>
    auto trace(const box<Ty, Aggregate> &ba,
               const W &w = W{},
     //          typename W::data_t &&volt = typename W::data_t{ w, " + "," - "},
               void *f = nullptr) -> typename W::data_t {
        return apply<Ty, Aggregate, W>
                (
                        ba,
                        w,
                       typename W::data_t(w,""," ")
                );
    }


    template<typename Ty, template<typename ...> typename Aggregate,
            typename W=stream_box<Ty, Aggregate>>
    auto trace_form(const box<Ty, Aggregate> &ba,
               const std::string& before, const std::string& after
                ) -> typename W::data_t {
        W w{};
        return apply(ba, w, w.mk_data_instance( before, after));
/*
        return apply_f<Ty, Aggregate, W>
                (
                        ba,
                        W{},
                        typename W::data_t{before,after},
                        (void *) trace_f2<Ty, Aggregate, W>
                );
                */
    }
}


#endif //BOX_TRACE_HPP
