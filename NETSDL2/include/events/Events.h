#pragma once

#include <SDL.h>

#include "Event.h"
#include "../core/Result.h"
#include "../core/None.h"
#include "../core/FunctionPointer.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Events
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// A function pointer used for callbacks that
		/// watch the event queue.
		/// </summary>
		/// <param name="userdata">What was passed as
		/// `userdata`.</param>
		/// <param name="event">The event that triggered
		/// the callback.</param>
		/// <returns>1 to permit event to be added to the
		/// queue, and 0 to disallow.</returns>
		public delegate int EventFilter(System::IntPtr userdata, Event% event);

		/// <summary>
		/// Functions for event handling.
		/// </summary>
		public ref struct Events abstract sealed
		{
		public:
			/// <summary>
			/// Add a callback to be triggered when an event
			/// is added to the event queue.
			/// </summary>
			/// <param name="filter">Function to call when
			/// an event happens.</param>
			/// <param name="userdata">A pointer that is
			/// passed to filter.</param>
			static void AddEventWatch(FunctionPointer<EventFilter^>^ filter,
				System::IntPtr userdata);

			/// <summary>
			/// Remove an event watch callback.
			/// </summary>
			/// <param name="filter">The function
			/// originally passed.</param>
			/// <param name="userdata">The pointer
			/// originally passed.</param>
			static void DelEventWatch(FunctionPointer<EventFilter^>^ filter,
				System::IntPtr userdata);

			/// <summary>
			/// Set the state of processing events by
			/// type.
			/// </summary>
			/// <param name="type">The type of event.
			/// </param>
			/// <param name="state">How to process the
			/// event.</param>
			/// <returns>The processing state of the
			/// event before this function makes any
			/// changes to it.</returns>
			static EventState SetEventState(EventType type, EventState state);

			/// <summary>
			/// Run a specific filter function on the
			/// current event queue, removing any events
			/// for which the filter returns 0.
			/// </summary>
			/// <param name="filter">The EventFilter
			/// function to call when an event happens.
			/// </param>
			/// <param name="userdata">A pointer that is
			/// passed to filter.</param>
			static void FilterEvents(EventFilter^ filter, System::IntPtr userdata);

			/// <summary>
			/// Clear events of a specific type from the
			/// event queue.
			/// </summary>
			/// <param name="type">The type of event to be
			/// cleared.</param>
			static void FlushEvent(EventType type);

			/// <summary>
			/// Clear events of a range of types from the
			/// event queue.
			/// </summary>
			/// <param name="minType">The low end of event
			/// type to be cleared, inclusive.</param>
			/// <param name="maxType">The high end of event
			/// type to be cleared, inclusive.</param>
			static void FlushEvents(EventType minType, EventType maxType);

			/// <summary>
			/// Query the current event filter.
			/// </summary>
			/// <param name="filter">The current callback
			/// function will be stored here. This is a
			/// native function pointer, so transform it
			/// to delegate or assign to C# function
			/// pointer.</param>
			/// <param name="userdata">The pointer that is
			/// passed to the current event filter will be
			/// stored here.</param>
			/// <returns></returns>
			static bool GetEventFilter([Out] System::IntPtr% filter, [Out]System::IntPtr% userdata);

			/// <summary>
			/// Query the current processing state of a
			/// specified EventType.
			/// </summary>
			/// <param name="type">EventType to query.
			/// </param>
			/// <returns>Disable or Enable.</returns>
			static EventState GetEventState(EventType type);

			/// <summary>
			/// Check for the existence of a certain event
			/// type in the event queue.
			/// </summary>
			/// <param name="type">The type of event to be
			/// queried.</param>
			/// <returns>true if events matching type are
			/// present, or false if events matching type
			/// are not present.</returns>
			static bool HasEvent(EventType type);

			/// <summary>
			/// Check for the existence of certain event
			/// types in the event queue.
			/// </summary>
			/// <param name="minType">The low end of event
			/// type to be queried, inclusive.</param>
			/// <param name="maxType">The high end of event
			/// type to be queried, inclusive.</param>
			/// <returns>true if events with type larger
			/// than or equal to minType and less than or
			/// equal to maxType are present, or false if
			/// not.</returns>
			static bool HasEvents(EventType minType, EventType maxType);

			/// <summary>
			/// Check the event queue for messages and
			/// optionally return them.
			/// </summary>
			/// <param name="events">Destination buffer for
			/// the retrieved events.</param>
			/// <param name="action">Action to take.</param>
			/// <param name="minType">Minimum value of the
			/// event type to be considered.</param>
			/// <param name="maxType">Maximum value of the
			/// event type to be considered.</param>
			/// <returns>The number of events actually
			/// stored or a negative error code on
			/// failure.</returns>
			static Result<int, int> PeepEvents(array<Event>^ events, EventAction action, EventType minType, EventType maxType);

			/// <summary>
			/// Poll for currently pending events.
			/// </summary>
			/// <param name="event">The <see cref="Event"/> structure to be
			/// filled with the next event from the queue.</param>
			/// <returns>Success if there is a pending event or Failure if
			/// there are none available.</returns>
			static Result<None^, None^> PollEvent([Out]Event% event);

			/// <summary>
			/// Pump the event loop, gathering events from
			/// the input devices.
			/// </summary>
			static void PumpEvents();

			/// <summary>
			/// Add an event to the event queue.
			/// </summary>
			/// <param name="event">The Event to be added
			/// to the queue.</param>
			/// <returns>1 on success, 0 if the event was
			/// filtered, or a negative error code on
			/// failure.</returns>
			static Result<int, int> PushEvent([In][IsReadOnly]Event% event);

			/// <summary>
			/// Whether an SDL_QUIT event is queued.
			/// </summary>
			static property bool QuitRequested
			{
				bool get();
			}

			/// <summary>
			/// Check whether there is an event in the queue.
			/// </summary>
			static property bool EventExist
			{
				bool get();
			}

			/// <summary>
			/// Allocate a set of user-defined events, and
			/// return the beginning event number for that
			/// set of events.
			/// </summary>
			/// <param name="numevents">The number of
			/// events to be allocated.</param>
			/// <returns>The beginning event number, or
			/// None if there are not enough user-defined
			/// events left.</returns>
			static Result<EventType, None^> RegisterEvents(int numevents);


			/// <summary>
			/// Set up a filter to process all events
			/// before they change internal state and are
			/// posted to the internal event queue.
			/// </summary>
			/// <param name="filter">Function to call when
			/// an event happens.</param>
			/// <param name="userdata">A pointer that is
			/// passed to filter.</param>
			static void SetEventFilter(FunctionPointer<EventFilter^>^ filter,
				System::IntPtr userdata);

			/// <summary>
			/// Wait indefinitely for the next available
			/// event.
			/// </summary>
			/// <param name="event">The Event structure to
			/// be filled in with the next event from the
			/// queue.</param>
			/// <returns>Success or Failure if there was an
			/// error while waiting for events.</returns>
			static Result<None^, None^> WaitEvent([Out]Event% event);

			/// <summary>
			/// Wait indefinitely for the next available
			/// event.
			/// </summary>
			/// <returns>Success or Failure if there was an
			/// error while waiting for events.</returns>
			static Result<None^, None^> WaitEvent();

			/// <summary>
			/// Wait until the specified timeout (in
			/// milliseconds) for the next available event.
			/// </summary>
			/// <param name="event">The Event structure to
			/// be filled in with the next event from the
			/// queue.</param>
			/// <param name="timeout">The maximum number of
			/// milliseconds to wait for the next available
			/// event.</param>
			/// <returns>Success or Failure if there was an
			/// error while waiting for events.</returns>
			static Result<None^, None^> WaitEventTimeout([Out]Event% event, int timeout);

			/// <summary>
			/// Wait until the specified timeout (in
			/// milliseconds) for the next available event.
			/// </summary>
			/// <param name="timeout">The maximum number of
			/// milliseconds to wait for the next available
			/// event.</param>
			/// <returns>Success or Failure if there was an
			/// error while waiting for events.</returns>
			static Result<None^, None^> WaitEventTimeout(int timeout);
		};
	}
}