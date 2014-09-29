#pragma once

#include <functional>
#include <stdexcept>

#define TEST(X) void X()
#define ASSERT_TRUE(x) timeit::assert::true_impl(x, "assertion failed: " #x)
#define ASSERT_EQUAL(x, y) timeit::assert::equal_impl(x, y, "assertion failed: " #x " == " #y);
#define ASSERT_THROW(e, f) timeit::assert::throw_impl<e>(f, "assertion failed: " #f "() doesn't throw " #e)

namespace timeit
{
    namespace assert
    {
        class assert_failed: public std::logic_error
        {
        public:
            explicit assert_failed(const char *what = "")
            : std::logic_error(what)
            {
            }
        };

        template <typename T>
        void true_impl(const T &x, const char *message)
        {
            if (!x) 
                throw assert_failed(message);
        }

        template <typename T>
        void equal_impl(const T &x, const T &y, const char *message)
        {
            if (!(x == y))
                throw assert_failed(message);
        }

        template <typename E>
        void throw_impl(const std::function<void ()> &f, const char *message)
        {
            try
            {
                f();
                throw assert_failed(message);
            }
            catch (const E &)
            {
                return;
            }
            catch (...)
            {
                throw assert_failed(message);
            }
        }
    
    }
}