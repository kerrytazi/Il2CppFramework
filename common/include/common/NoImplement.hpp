#pragma once

struct _NoImplement
{
	_NoImplement() = delete;
	//~_NoImplement() = delete;
	_NoImplement(const _NoImplement&) = delete;
	_NoImplement(_NoImplement&&) = delete;
	_NoImplement& operator=(const _NoImplement&) = delete;
	_NoImplement& operator=(_NoImplement&&) = delete;
};
