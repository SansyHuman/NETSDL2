#include "../../include/core/Result.h"

using namespace NETSDL2::Core;
using namespace System;

generic<class Success, class Failure>
inline Result<Success, Failure> Result<Success, Failure>::MakeResult(Success result)
{
	Result<Success, Failure> res;
	res.result = result;
	res.resultType = Result::Type::Succeeded;

	return res;
}

generic<class Success, class Failure>
Result<Success, Failure> Result<Success, Failure>::MakeFailure(Failure error)
{
	Result<Success, Failure> res;
	res.error = error;
	res.resultType = Result::Type::Failed;

	return res;
}

generic<class Success, class Failure>
System::String^ NETSDL2::Core::Result<Success, Failure>::ToString()
{
	switch(resultType)
	{
	case Type::Succeeded:
		return String::Format("Success({0})", result);
	case Type::Failed:
		return String::Format("Failure({0})", error);
	}
}

generic<class Success, class Failure>
Result<Success, Failure>::Type Result<Success, Failure>::ResultType::get()
{
	return resultType;
}

generic<class Success, class Failure>
bool Result<Success, Failure>::IsSuccess::get()
{
	return resultType == Type::Succeeded;
}

generic<class Success, class Failure>
bool Result<Success, Failure>::IsFailure::get()
{
	return resultType == Type::Failed;
}

generic<class Success, class Failure>
Success Result<Success, Failure>::ResultValue::get()
{
	if(resultType == Type::Failed)
		throw gcnew InvalidOperationException("The result is failure but tried to acquire success result.");

	return result;
}

generic<class Success, class Failure>
Failure Result<Success, Failure>::ErrorValue::get()
{
	if(resultType == Type::Succeeded)
		throw gcnew InvalidOperationException("The result is success but tried to acquire error.");

	return error;
}

generic<class Success, class Failure>
Result<Success, Failure>::operator Result<Success, Failure>(Success result)
{
	return Result<Success, Failure>::MakeResult(result);
}
