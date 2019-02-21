#pragma once

#include <variant>
#include <memory>

///wte with context

namespace stepworks::matching::atom::wtex {

	template <typename R, typename Ta, typename Cx>
	struct _ab {
		using F = R(*) (const Ta&, const Cx*);
		F _f;
		using construction_arg = F;
		R operator()(const Ta& a) const {
			return _f(a);
		}
	};

	template <typename R, typename Ta, typename Cx>
	struct _M;

	template <typename R, typename Ta, typename Cx>
	struct _M {
		using Qw = bool(*) (const Ta&, const Cx*);
		using F =R(*) (const Ta&, const Cx*);

		using Op = std::variant<
			R,
			_ab<R, Ta ,Cx>,
			std::unique_ptr <  _M<R, Ta, Cx> >
		>;
		
		using construction_arg = F;     ///@@@!!!

		/////incomplete? 
		_M(Qw q, _ab<R, Ta, Cx>&& l, _ab<R, Ta, Cx>&& r) :_when(q), _then(std::move(l)), _else(std::move(r)) {}
		
		_M(Qw q, typename  _ab<R, Ta, Cx>::construction_arg l, typename  _ab<R, Ta, Cx>::construction_arg r) :_when(q),
			_then(_ab<R, Ta,Cx>{l}),
			_else(_ab<R, Ta,Cx>  {r}) {}

		_M(Qw q, typename  _ab<R, Ta,Cx>::construction_arg l,   _M<R,Ta,Cx>*r) :_when(q),
			_then(_ab<R, Ta,Cx>{l}),
			_else(std::unique_ptr< _M<R, Ta,Cx> >(r)) {}

		_M(Qw q, _M* l,  Op&& r) :_when(q),
			_then( std::move(std::unique_ptr< _M<R, Ta,Cx> >{l})),
			_else( std::move(r) ) {}


		_M(Qw q, _M* l , const Op& r) :_when(q), _then(l), _else(r) {}  //?
		
		
		_M(Qw q, Op&& l, Op&& r) :_when(q), _then(std::move(l)), _else(std::move(r)) {}

		_M(Qw q, const  _M* l, Op&& r) :_when(q), _then(  l  ), _else(std::move(r)) {}

		_M(Qw q, Op&& l, const  _M* r) :_when(q), _then(std::move(l)), _else(r) {}

		_M(Qw q, const _M* l, const _M* r) :_when(q), _then(l), _else(r) {}
		
		/**/
		//_M(Qw q, typename  _M<R, Ta>::construction_arg l, typename  _ab<R, Ta>::construction_arg r) :_when(q), _then(l), _else(r) {}

		_M(Qw q, typename  _ab<R, Ta,Cx>::construction_arg l, 
			  _M<R, Ta,Cx> r) :_when(q), _then(l), _else(r) {}

		Qw _when;
		Op _then;
		Op _else;

		constexpr R apply(const Op& op, const Ta&a, const Cx* context ) const {
			struct vis {
				const Ta& _a;
                                const Cx* context;
				auto operator()( const R& v)const ->R { return v; }
				auto operator()(const _ab<R, Ta ,Cx>& v)const->R { return  v._f(_a , context); }
				auto operator()(const std::unique_ptr  < _M<R, Ta,Cx >>&  v)const ->R 
				{
					return  (*v)( _a, context); 
				}
			};
			return std::visit(vis{ a , context}, std::forward<const Op&>(op));
		}

		R operator()(const Ta& a, const Cx* context ) const {
			return _when(a, context) ?
				apply( _then, a, context) : apply ( _else,a, context);
		}
	
	};


}
