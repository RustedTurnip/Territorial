/*!
 * \file ResourceHolder.h : contains the ResourceHolder class declaration
 */

#ifndef BOOK_RESOURCEHOLDER_HPP
#define BOOK_RESOURCEHOLDER_HPP

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

/*!
 * \class Provides a generic class for holding resources
 */
template <typename Resource, typename Identifier>
class ResourceHolder
{
	public:
		void load(Identifier id, const std::string& filename);

		template <typename Parameter>
		void load(Identifier id, const std::string& filename, const Parameter& secondParam); /*!< Declared for the sf::Shader class which can take a second parameter */

		Resource& get(Identifier id);
		const Resource& get(Identifier id) const;


	private:
		void insertResource(Identifier id, std::unique_ptr<Resource> resource);


	private:
		std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};

#include "ResourceHolder.inl"
#endif // BOOK_RESOURCEHOLDER_HPP
