#ifndef LOCKBOX_HPP
#define LOCKBOX_HPP

#include <mutex>

namespace Zen::Parallel {
/**
 * Lockbox is a container which enables multiple threads to access the same
 * value.
 *
 * The lockbox **does not** prevent race conditions. Two threads attempting to
 * write to the lockbox will still race to access the internal mutex. What it
 * does enable is a single provider, multiple consumer data containerization.
 */
template <typename T> class Lockbox {
public:
  /**
   * Sets the internal value to that of val.
   *
   * @param val The value to store.
   */
  void Set(T val) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_val = val;
  };

  /**
   * Returns a copy of the contained object.
   *
   * @return A copy of the internal object.
   */
  auto Get() -> T {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_val;
  }

private:
  T m_val;
  std::mutex m_mutex;
};

} // namespace Zen::Parallel

#endif // LOCKBOX_HPP
