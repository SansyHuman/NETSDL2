#pragma once

#include <SDL.h>
#include "GLAttr.h"
#include "../core/Result.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Core
	{
		ref class None;
	}

	namespace Video
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// OpenGL context object.
		/// </summary>
		public ref class GLContext
		{
		private:
			SDL_GLContext context;
			static System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, GLContext^>^ nativeContextConnections;
			static GLContext()
			{
				nativeContextConnections = gcnew System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, GLContext^>();
			}

		internal:
			GLContext(SDL_GLContext context);

		public:
			~GLContext();
			!GLContext();

			/// <summary>
			/// Delete an OpenGL context.
			/// </summary>
			/// <param name="context">OpenGL context to be deleted.</param>
			static void DeleteContext(GLContext^ context);

		internal:
			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			static Result<GLContext^, None^> GetCurrentContext();

			property SDL_GLContext NativeContext
			{
				[MethodImpl(MethodImplOptions::AggressiveInlining)]
				SDL_GLContext get();
			}
		};
	}
}