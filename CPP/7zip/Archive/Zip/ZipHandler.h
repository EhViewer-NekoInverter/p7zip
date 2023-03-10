// Zip/Handler.h

#ifndef __ZIP_HANDLER_H
#define __ZIP_HANDLER_H

#include "../../../Common/DynamicBuffer.h"
#include "../../ICoder.h"
#include "../IArchive.h"

#include "../../Common/CreateCoder.h"

#include "ZipIn.h"
#include "ZipCompressionMode.h"

namespace NArchive {
namespace NZip {

class CHandler:
  public IInArchive,
  #ifndef EXTRACT_ONLY
  public IOutArchive,
  public ISetProperties,
  #endif
  PUBLIC_ISetCompressCodecsInfo
  public CMyUnknownImp
{
public:
  MY_QUERYINTERFACE_BEGIN2(IInArchive)
  #ifndef EXTRACT_ONLY
  MY_QUERYINTERFACE_ENTRY(IOutArchive)
  MY_QUERYINTERFACE_ENTRY(ISetProperties)
  #endif
  QUERY_ENTRY_ISetCompressCodecsInfo
  MY_QUERYINTERFACE_END
  MY_ADDREF_RELEASE

  INTERFACE_IInArchive(;)
  #ifndef EXTRACT_ONLY
  INTERFACE_IOutArchive(;)
  #endif

  #ifndef EXTRACT_ONLY
  STDMETHOD(SetProperties)(const wchar_t * const *names, const PROPVARIANT *values, UInt32 numProps);
  #endif

  DECL_ISetCompressCodecsInfo

  CHandler();
private:
  CObjectVector<CItemEx> m_Items;
  CInArchive m_Archive;

  CBaseProps _props;

  int m_MainMethod;
  bool m_ForceAesMode;
  bool m_WriteNtfsTimeExtra;
  bool _removeSfxBlock;
  bool m_ForceLocal;
  bool m_ForceUtf8;
  bool _forceCodePage;
  UInt32 _specifiedCodePage;

  DECL_EXTERNAL_CODECS_VARS

  void InitMethodProps()
  {
    _props.Init();
    m_MainMethod = -1;
    m_ForceAesMode = false;
    m_WriteNtfsTimeExtra = true;
    _removeSfxBlock = false;
    m_ForceLocal = false;
    m_ForceUtf8 = false;
    _forceCodePage = false;
    _specifiedCodePage = CP_OEMCP;
  }
};

}}

#endif
