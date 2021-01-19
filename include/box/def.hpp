//
// Created by karsten on 24.11.20.
//

#ifndef BOX_DEF_HPP
#define BOX_DEF_HPP

#include <variant>
#include <detect/detect_allocator.hpp>
#include <ostream>

using stepworks::detect::has_allocator;

namespace stepworks::bxx{

   // template <typename ...> struct box;

    template <typename Ty, template<typename ...> typename Aggregation>
    struct box{

        using base_t = Ty;
        using agg_t = Aggregation<box<base_t, Aggregation> >;
        using type = std::variant<Ty, agg_t>;

        using type_enum=enum{eatom=0, eaggregate=1};

        struct agg_position{
            const agg_t& _container;
            typename agg_t::const_iterator _it;
        };

        type _value;

        box(type v) : _value(std::forward<type>(v)) {     //   std::cout<<"-1-";
        }

     //   using is_allocable_container = typename has_allocator<typename box<Ty, Aggregation>::agg_t>::type;

        box(agg_t&& a) : _value(std::move(a)) {      //   std::cout<<"-3-";
        }

        box(const agg_t& a) : _value(a) {      //   std::cout<<"-3-";
        }

        box() {
            _value=agg_t {};
        }

        box(std::initializer_list< //std::variant<Ty,
                typename   box<Ty, Aggregation>::type  > il);



        template<typename B =  typename  box<Ty,std::initializer_list>::type, typename =     typename std::enable_if_t
                <
                       ! std::is_same<B, type>::value>::type>

        box( const  B& b ){
            _value=b;
        }

        template<typename I = const typename box<Ty, Aggregation>::agg_t, typename =     typename std::enable_if_t
                <  has_allocator<I>::value> >
        box(
                std::initializer_list<
                        typename box<Ty, Aggregation>::type> il, const I &a
        );

        box(type_enum  e) {
            _value= (e) ? type (agg_t {}) : type(base_t{});
        }

        operator type () const{
            return _value;
        }

        friend std::ostream& operator <<   (std::ostream& s, const box<Ty, Aggregation>& o){
            s << to_string(o);
            return s;
        };
    };


    }





#endif //BOX_DEF_HPP
