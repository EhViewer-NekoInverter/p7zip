// TarHandler.h

#ifndef __TAR_HANDLER_H
#define __TAR_HANDLER_H

#include "../../../Common/MyCom.h"

#include "../../../Windows/PropVariant.h"

#include "../../Compress/CopyCoder.h"

#include "../IArchive.h"

#include "TarIn.h"

namespace NArchive {
namespace NTar {

class CHandler:
  public IInArchive,
  public IArchiveOpenSeq,
  public IInArchiveGetStream,
  #ifndef EXTRACT_ONLY
  public ISetProperties,
  public IOutArchive,
  #endif
  public CMyUnknownImp
{
public:
  CObjectVector<CItemEx> _items;
  CMyComPtr<IInStream> _stream;
  CMyComPtr<ISequentialInStream> _seqStream;
private:
  UInt32 _curIndex;
  bool _latestIsRead;
  CItemEx _latestItem;

  UInt64 _phySize;
  UInt64 _headersSize;
  bool _phySizeDefined;
  EErrorType _error;
  bool _isArc;

  // bool _isSparse;
  bool _thereIsPaxExtendedHeader;

  bool _forceCodePage;
  UInt32 _specifiedCodePage;
  UInt32 _curCodePage;
  UInt32 _openCodePage;

  NCompress::CCopyCoder *copyCoderSpec;
  CMyComPtr<ICompressCoder> copyCoder;

  HRESULT ReadItem2(ISequentialInStream *stream, bool &filled, CItemEx &itemInfo);
  HRESULT Open2(IInStream *stream, IArchiveOpenCallback *callback);
  HRESULT SkipTo(UInt32 index);
  void TarStringToUnicode(const AString &s, NWindows::NCOM::CPropVariant &prop, bool toOs = false) const;
public:
  #ifndef EXTRACT_ONLY
  MY_UNKNOWN_IMP5(
    IInArchive,
    IArchiveOpenSeq,
    IInArchiveGetStream,
    ISetProperties,
    IOutArchive
  )
  #else
  MY_UNKNOWN_IMP3(
      IInArchive,
      IArchiveOpenSeq,
      IInArchiveGetStream
  )
  #endif

  INTERFACE_IInArchive(;)
  #ifndef EXTRACT_ONLY
  INTERFACE_IOutArchive(;)
  #endif
  STDMETHOD(OpenSeq)(ISequentialInStream *stream);
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
  #ifndef EXTRACT_ONLY
  STDMETHOD(SetProperties)(const wchar_t * const *names, const PROPVARIANT *values, UInt32 numProps);
  #endif

  void Init();
  CHandler();
};

}}

#endif
