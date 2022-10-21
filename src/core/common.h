#pragma once

namespace zen::remote {

/**
 * Iterates the container of std::weak_ptr. If the weak_ptr is empty, it is
 * removed from the container.
 */
template <template <class> typename C, typename T>
void
ForEachWeakPtr(C<std::weak_ptr<T>> &container,
    std::function<void(std::shared_ptr<T>)> func)
{
  // Add other types of container if needed
  static_assert(std::is_same<C<int>, std::list<int>>::value ||
                    std::is_same<C<int>, std::vector<int>>::value,
      "C must be one of [std::list, std::vector]");

  for (auto it = container.begin(); it != container.end();) {
    if (auto item = (*it).lock()) {
      func(item);
      ++it;
    } else {
      it = container.erase(it);
    }
  }
}

#define DISABLE_MOVE_AND_COPY(Class)        \
  Class(const Class &) = delete;            \
  Class(Class &&) = delete;                 \
  Class &operator=(const Class &) = delete; \
  Class &operator=(Class &&) = delete

inline constexpr uint16_t kDiscoverPort = 9983;  // listen in server
inline constexpr uint16_t kGrpcPort = 50051;     // listen in client

}  // namespace zen::remote
