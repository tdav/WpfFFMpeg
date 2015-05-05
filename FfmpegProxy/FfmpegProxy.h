// FfmpegProxy.h
#pragma once

#include "NewFrameEventArgs.h"

using namespace System;

namespace FfmpegProxy
{
	using namespace System::Runtime::InteropServices;
	using namespace System::Threading;

	[UnmanagedFunctionPointerAttribute(CallingConvention::Cdecl)]
	delegate int InterruptAVDelegate(void* ptr);


public
	ref class FFMPEGProxy
	{
	private:
		static log4net::ILog ^ LOG = log4net::LogManager::GetLogger(System::Reflection::MethodBase::GetCurrentMethod()->DeclaringType);

		bool isDisposed;
		FFMpeg::AVFormatContext* avContext;
		int videoStreamIndex;
		FFMpeg::AVCodecContext* videoCodecContext;

		InterruptAVDelegate^ interruptDelegate;
		CancellationTokenSource ^ stopSource;
		ManualResetEventSlim ^ loopEnded;

		int InterruptCallback(void* ptr);

	public:
		FFMPEGProxy();
		!FFMPEGProxy();
		~FFMPEGProxy();
		void Open(String ^ uri);
		event EventHandler<NewFrameEventArgs ^> ^ NewFrame;
	};
}
