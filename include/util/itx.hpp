#pragma once

#include <array>
#include <variant>
#include <optional>
#include <cstddef>
#include <rw/rforward.hpp>
#include <rw/wforward.hpp>
#include <util/indicator_value.hpp>
#include <reposition.hpp>

using stepworks::fw;
using stepworks::wforward;

namespace  stepworks{
    
    
    template <typename Elm, typename Corpus>
    struct itx{
        static_assert( sizeof(Elm) <= sizeof(Corpus),"size of element must not be greter then size of corpus");
        static const std::size_t size_factor =  sizeof(Corpus) / sizeof(Elm);
        static const bool   has_rest =   (sizeof(Corpus) % sizeof(Elm))>0;
        static const std::size_t size_effectiv = size_factor+ (has_rest ? 1 : 0);
        
        using box_t = union {
            std::array<Elm, size_effectiv > _arr;
            Corpus       _corpus;
        } ;
        
        using return_t = std::variant<Corpus, fail_value<std::size_t>>;
       
        template < template <typename...> typename stream_t >
        static constexpr auto read_corpus( fw<Elm, stream_t, std::optional>&& strm )->std::pair<return_t, fw<Elm, stream_t, std::optional>>{
            box_t _box;
            for (std::size_t k=0;  k< size_effectiv; ++k){
                auto as = _go_(strm);
                if (as.first)
                    _box._arr[k] = _asserted( as.first) ;
                else
                    return std::make_pair( stepworks::make_fail_value(k), std::move(strm) );
            }
            return std::make_pair( _box._corpus, std::move(strm));
        }
        
       
       template <  template <typename...> typename stream_t >
        static
        constexpr 
        auto write_corpus( wforward<Elm, stream_t, std::optional> strm, const box_t& box )-> wforward<Elm, stream_t, std::optional>{
          for ( auto itr =box._arr.begin(); itr != box._arr.end(); itr++  ){
                _go_(std::move(strm),* itr);
            }
            return std::move(strm);
        }
       
       
        
        template < template <typename...> typename Form >
        static 
        constexpr 
        auto write_corpus_forward_ret( Form<Elm>&& form, const Corpus& box ){
            auto ret =write_corpus( wforward< Elm, Form, std::optional> { std::move(form) }, (const box_t&)  box);
            return std::move(ret._dest);
        }
        
          //returns former position on fail
         template < template <typename...> typename stream_t >
        static constexpr auto try_read_corpus( fw<Elm, stream_t, std::optional>&& strm )->std::pair<return_t, fw<Elm, stream_t, std::optional>>{
          
            using fw_t = fw<Elm, stream_t, std::optional>;
         
            static_assert( stepworks::has_reposition<  fw_t >::value,"reposition support is needed"  );
           
            auto here = get_position(strm);
            box_t _box;
            for (std::size_t k=0;  k< size_effectiv; ++k){
                auto as = _go_(std::move( strm) );
                if (as.first)
                    _box._arr[k] = _asserted( as.first) ;
                else{
                    set_position(strm, std::move(here) );
                    return std::make_pair( stepworks::make_fail_value(k), std::move(strm) );
                }
            }
            return std::make_pair( _box._corpus, std::move(strm));
            
        }
        
        template <  template <typename...> typename stream_t >        
        static  auto read_corpus_v( stream_t<Elm>&& c ){
            auto ret =try_read_corpus<stream_t>(fw<Elm, stream_t, std::optional>{ std::move(c) }  );
            return ret;
        }
    };
    
    
    
}

