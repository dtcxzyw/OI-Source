#pragma once
#include "../Common.hpp"
#include <Windows.h>
#include <system_error>
class Win32APIError final
    : public std::error_category {
private:
    SourceLocation mLoc;

public:
    Win32APIError(const SourceLocation& loc);
    const char* name() const noexcept override;
    std::string
    message(int cond) const noexcept override;
    ~Win32APIError() override = default;
};
[[noreturn]] void
reportError(const SourceLocation& loc =
                SourceLocation::current());
class Handle final : private Unmovable {
private:
    HANDLE mHandle;

public:
    Handle(HANDLE handle,
           const SourceLocation& loc =
               SourceLocation::current());
    HANDLE get() const noexcept;
    ~Handle();
};
void winAssert(WINBOOL res,
               const SourceLocation& loc =
                   SourceLocation::current());
