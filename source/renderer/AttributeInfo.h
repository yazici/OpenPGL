#ifndef _RENDERER_ATTRIBUTEINFO_HPP
#define _RENDERER_ATTRIBUTEINFO_HPP

#include <vector>

namespace pgl
{
	class AttributeLayout;

    struct AttributeInfo
    {
        int index;
        unsigned int size;
        unsigned int type;
		unsigned int normalize;
		unsigned int pointer;

		operator AttributeLayout() const;

		static AttributeInfo POSITION;
		static AttributeInfo NORMAL;
		static AttributeInfo TEXCOORD;
    };

    class AttributeLayout
    {
	public:

		AttributeLayout();

		AttributeLayout(const AttributeLayout &a);
		
		AttributeLayout(AttributeLayout &&a);

		~AttributeLayout();

		void push(const AttributeInfo &a);

		const AttributeInfo &get(size_t i) const;

		unsigned int stride() const;

		size_t length() const;

		AttributeLayout &operator|(const AttributeInfo &a);

	private:

		std::vector<AttributeInfo> _attribs;
		unsigned int _stride;
    };

	AttributeLayout operator|(const AttributeInfo &a1, const AttributeInfo &a2);
}

#endif //!_RENDERER_ATTRIBUTEINFO_HPP
