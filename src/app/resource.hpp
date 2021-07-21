#pragma once
#include <optional>

namespace app {

template<typename T>
class Resource {
	using loadingFunction_t = T (*)();

	const loadingFunction_t loadingFunction;
	mutable std::optional<T> resource;

public:
	Resource(const loadingFunction_t loadingFunction);

	T& get() const;
};

template<typename T>
Resource<T>::Resource(const loadingFunction_t loadingFunction)
		: loadingFunction{loadingFunction}, resource{} {}

template<typename T>
T& Resource<T>::get() const {
	if (!resource.has_value()) {
		resource.emplace(loadingFunction());
	}
	return resource.value();
}

} // namespace app
