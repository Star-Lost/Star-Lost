#pragma once

struct non_copyable
{
	non_copyable() = default;
	non_copyable(const non_copyable &) = delete;
};

struct non_assignable
{
	non_assignable() = default;
	non_assignable &operator=(const non_assignable &) = delete;
};

struct non_moveable
{
	non_moveable() = default;
	non_moveable(non_moveable &&) = delete;
};

struct moveable : public non_assignable, public non_copyable
{
	moveable() = default;
};

struct copyable : public non_assignable, public non_moveable
{
	copyable() = default;
};

struct assignable : public non_copyable, public non_moveable
{
	assignable() = default;
};

struct unique : public non_assignable, public non_copyable, public non_moveable 
{
	unique() = default;
};