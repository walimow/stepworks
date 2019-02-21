#include <variant>
#include <memory>

namespace stepworks::matching::atom::wte {

	template <typename R, typename Ta>
	struct _ab {
		using F = R(*) (const Ta&);
		F _f;
		using construction_arg = F;
		R operator()(const Ta& a) const {
			return _f(a);
		}
	};

	template <typename R, typename Ta>
	struct _M;

	template <typename R, typename Ta>
	struct _M {
		using Qw = bool(*) (const Ta&);
		using F =R(*) (const Ta&);

		using Op = std::variant<
			R,
			_ab<R, Ta >,
			std::unique_ptr <  _M<R, Ta> >
		>;
		
		using construction_arg = F;     ///@@@!!!

		/////incomplete? 
		_M(Qw q, _ab<R, Ta>&& l, _ab<R, Ta>&& r) :_when(q), _then(std::move(l)), _else(std::move(r)) {}
		
		_M(Qw q, typename  _ab<R, Ta>::construction_arg l, typename  _ab<R, Ta>::construction_arg r) :_when(q),
			_then(_ab<R, Ta>{l}),
			_else(_ab<R, Ta>  {r}) {}

		_M(Qw q, typename  _ab<R, Ta>::construction_arg l,   _M<R,Ta>*r) :_when(q),
			_then(_ab<R, Ta>{l}),
			_else(std::unique_ptr< _M<R, Ta> >(r)) {}

		_M(Qw q, _M* l,  Op&& r) :_when(q),
			_then( std::move(std::unique_ptr< _M<R, Ta> >{l})),
			_else( std::move(r) ) {}


		_M(Qw q, _M* l , const Op& r) :_when(q), _then(l), _else(r) {}  //?
		
		
		_M(Qw q, Op&& l, Op&& r) :_when(q), _then(std::move(l)), _else(std::move(r)) {}

		_M(Qw q, const  _M* l, Op&& r) :_when(q), _then(  l  ), _else(std::move(r)) {}

		_M(Qw q, Op&& l, const  _M* r) :_when(q), _then(std::move(l)), _else(r) {}

		_M(Qw q, const _M* l, const _M* r) :_when(q), _then(l), _else(r) {}
		
		/**/
		//_M(Qw q, typename  _M<R, Ta>::construction_arg l, typename  _ab<R, Ta>::construction_arg r) :_when(q), _then(l), _else(r) {}

		_M(Qw q, typename  _ab<R, Ta>::construction_arg l, 
			  _M<R, Ta> r) :_when(q), _then(l), _else(r) {}

		Qw _when;
		Op _then;
		Op _else;

		constexpr R apply(const Op& op, const Ta&a) const {
			struct vis {
				const Ta& _a;
				auto operator()( const R& v)const ->R { return v; }
				auto operator()(const _ab<R, Ta >& v)const->R { return  v._f(_a); }
				auto operator()(const std::unique_ptr  < _M<R, Ta >>&  v)const ->R 
				{
					return  (*v)( _a); 
				}
			};
			return std::visit(vis{ a }, std::forward<const Op&>(op));
		}

		R operator()(const Ta& a) const {
			return _when(a) ?
				apply( _then, a) : apply ( _else,a);
		}
	
	};


}
