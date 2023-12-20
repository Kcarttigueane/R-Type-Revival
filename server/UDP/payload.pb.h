// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: payload.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_payload_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_payload_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3019000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3019006 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_payload_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_payload_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_payload_2eproto;
namespace rtype {
class Event;
struct EventDefaultTypeInternal;
extern EventDefaultTypeInternal _Event_default_instance_;
class Payload;
struct PayloadDefaultTypeInternal;
extern PayloadDefaultTypeInternal _Payload_default_instance_;
class PayloadHeader;
struct PayloadHeaderDefaultTypeInternal;
extern PayloadHeaderDefaultTypeInternal _PayloadHeader_default_instance_;
}  // namespace rtype
PROTOBUF_NAMESPACE_OPEN
template<> ::rtype::Event* Arena::CreateMaybeMessage<::rtype::Event>(Arena*);
template<> ::rtype::Payload* Arena::CreateMaybeMessage<::rtype::Payload>(Arena*);
template<> ::rtype::PayloadHeader* Arena::CreateMaybeMessage<::rtype::PayloadHeader>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace rtype {

enum Type : int {
  PLAYER = 0,
  BULLET = 1,
  ENEMY = 2,
  WALL = 3,
  BONUS = 4,
  Type_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  Type_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool Type_IsValid(int value);
constexpr Type Type_MIN = PLAYER;
constexpr Type Type_MAX = BONUS;
constexpr int Type_ARRAYSIZE = Type_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* Type_descriptor();
template<typename T>
inline const std::string& Type_Name(T enum_t_value) {
  static_assert(::std::is_same<T, Type>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function Type_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    Type_descriptor(), enum_t_value);
}
inline bool Type_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, Type* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<Type>(
    Type_descriptor(), name, value);
}
enum EventType : int {
  MOVEUP = 0,
  MOVEDOWN = 1,
  MOVELEFT = 2,
  MOVERIGHT = 3,
  SHOOT = 4,
  QUIT = 5,
  EventType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EventType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EventType_IsValid(int value);
constexpr EventType EventType_MIN = MOVEUP;
constexpr EventType EventType_MAX = QUIT;
constexpr int EventType_ARRAYSIZE = EventType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EventType_descriptor();
template<typename T>
inline const std::string& EventType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EventType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EventType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EventType_descriptor(), enum_t_value);
}
inline bool EventType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EventType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EventType>(
    EventType_descriptor(), name, value);
}
// ===================================================================

class PayloadHeader final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:rtype.PayloadHeader) */ {
 public:
  inline PayloadHeader() : PayloadHeader(nullptr) {}
  ~PayloadHeader() override;
  explicit constexpr PayloadHeader(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PayloadHeader(const PayloadHeader& from);
  PayloadHeader(PayloadHeader&& from) noexcept
    : PayloadHeader() {
    *this = ::std::move(from);
  }

  inline PayloadHeader& operator=(const PayloadHeader& from) {
    CopyFrom(from);
    return *this;
  }
  inline PayloadHeader& operator=(PayloadHeader&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const PayloadHeader& default_instance() {
    return *internal_default_instance();
  }
  static inline const PayloadHeader* internal_default_instance() {
    return reinterpret_cast<const PayloadHeader*>(
               &_PayloadHeader_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(PayloadHeader& a, PayloadHeader& b) {
    a.Swap(&b);
  }
  inline void Swap(PayloadHeader* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PayloadHeader* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  PayloadHeader* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<PayloadHeader>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const PayloadHeader& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const PayloadHeader& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PayloadHeader* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "rtype.PayloadHeader";
  }
  protected:
  explicit PayloadHeader(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kBodySizeFieldNumber = 1,
  };
  // uint32 body_size = 1;
  void clear_body_size();
  uint32_t body_size() const;
  void set_body_size(uint32_t value);
  private:
  uint32_t _internal_body_size() const;
  void _internal_set_body_size(uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:rtype.PayloadHeader)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  uint32_t body_size_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_payload_2eproto;
};
// -------------------------------------------------------------------

class Payload final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:rtype.Payload) */ {
 public:
  inline Payload() : Payload(nullptr) {}
  ~Payload() override;
  explicit constexpr Payload(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Payload(const Payload& from);
  Payload(Payload&& from) noexcept
    : Payload() {
    *this = ::std::move(from);
  }

  inline Payload& operator=(const Payload& from) {
    CopyFrom(from);
    return *this;
  }
  inline Payload& operator=(Payload&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Payload& default_instance() {
    return *internal_default_instance();
  }
  static inline const Payload* internal_default_instance() {
    return reinterpret_cast<const Payload*>(
               &_Payload_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Payload& a, Payload& b) {
    a.Swap(&b);
  }
  inline void Swap(Payload* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Payload* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Payload* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Payload>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Payload& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Payload& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Payload* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "rtype.Payload";
  }
  protected:
  explicit Payload(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIdSpriteFieldNumber = 1,
    kPosXFieldNumber = 2,
    kPosYFieldNumber = 3,
    kWidthFieldNumber = 4,
    kHeightFieldNumber = 5,
  };
  // uint32 idSprite = 1;
  void clear_idsprite();
  uint32_t idsprite() const;
  void set_idsprite(uint32_t value);
  private:
  uint32_t _internal_idsprite() const;
  void _internal_set_idsprite(uint32_t value);
  public:

  // uint32 posX = 2;
  void clear_posx();
  uint32_t posx() const;
  void set_posx(uint32_t value);
  private:
  uint32_t _internal_posx() const;
  void _internal_set_posx(uint32_t value);
  public:

  // uint32 posY = 3;
  void clear_posy();
  uint32_t posy() const;
  void set_posy(uint32_t value);
  private:
  uint32_t _internal_posy() const;
  void _internal_set_posy(uint32_t value);
  public:

  // uint32 width = 4;
  void clear_width();
  uint32_t width() const;
  void set_width(uint32_t value);
  private:
  uint32_t _internal_width() const;
  void _internal_set_width(uint32_t value);
  public:

  // uint32 height = 5;
  void clear_height();
  uint32_t height() const;
  void set_height(uint32_t value);
  private:
  uint32_t _internal_height() const;
  void _internal_set_height(uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:rtype.Payload)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  uint32_t idsprite_;
  uint32_t posx_;
  uint32_t posy_;
  uint32_t width_;
  uint32_t height_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_payload_2eproto;
};
// -------------------------------------------------------------------

class Event final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:rtype.Event) */ {
 public:
  inline Event() : Event(nullptr) {}
  ~Event() override;
  explicit constexpr Event(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Event(const Event& from);
  Event(Event&& from) noexcept
    : Event() {
    *this = ::std::move(from);
  }

  inline Event& operator=(const Event& from) {
    CopyFrom(from);
    return *this;
  }
  inline Event& operator=(Event&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Event& default_instance() {
    return *internal_default_instance();
  }
  static inline const Event* internal_default_instance() {
    return reinterpret_cast<const Event*>(
               &_Event_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(Event& a, Event& b) {
    a.Swap(&b);
  }
  inline void Swap(Event* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Event* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Event* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Event>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Event& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Event& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Event* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "rtype.Event";
  }
  protected:
  explicit Event(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kEventFieldNumber = 1,
  };
  // .rtype.EventType event = 1;
  void clear_event();
  ::rtype::EventType event() const;
  void set_event(::rtype::EventType value);
  private:
  ::rtype::EventType _internal_event() const;
  void _internal_set_event(::rtype::EventType value);
  public:

  // @@protoc_insertion_point(class_scope:rtype.Event)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  int event_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_payload_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// PayloadHeader

// uint32 body_size = 1;
inline void PayloadHeader::clear_body_size() {
  body_size_ = 0u;
}
inline uint32_t PayloadHeader::_internal_body_size() const {
  return body_size_;
}
inline uint32_t PayloadHeader::body_size() const {
  // @@protoc_insertion_point(field_get:rtype.PayloadHeader.body_size)
  return _internal_body_size();
}
inline void PayloadHeader::_internal_set_body_size(uint32_t value) {
  
  body_size_ = value;
}
inline void PayloadHeader::set_body_size(uint32_t value) {
  _internal_set_body_size(value);
  // @@protoc_insertion_point(field_set:rtype.PayloadHeader.body_size)
}

// -------------------------------------------------------------------

// Payload

// uint32 idSprite = 1;
inline void Payload::clear_idsprite() {
  idsprite_ = 0u;
}
inline uint32_t Payload::_internal_idsprite() const {
  return idsprite_;
}
inline uint32_t Payload::idsprite() const {
  // @@protoc_insertion_point(field_get:rtype.Payload.idSprite)
  return _internal_idsprite();
}
inline void Payload::_internal_set_idsprite(uint32_t value) {
  
  idsprite_ = value;
}
inline void Payload::set_idsprite(uint32_t value) {
  _internal_set_idsprite(value);
  // @@protoc_insertion_point(field_set:rtype.Payload.idSprite)
}

// uint32 posX = 2;
inline void Payload::clear_posx() {
  posx_ = 0u;
}
inline uint32_t Payload::_internal_posx() const {
  return posx_;
}
inline uint32_t Payload::posx() const {
  // @@protoc_insertion_point(field_get:rtype.Payload.posX)
  return _internal_posx();
}
inline void Payload::_internal_set_posx(uint32_t value) {
  
  posx_ = value;
}
inline void Payload::set_posx(uint32_t value) {
  _internal_set_posx(value);
  // @@protoc_insertion_point(field_set:rtype.Payload.posX)
}

// uint32 posY = 3;
inline void Payload::clear_posy() {
  posy_ = 0u;
}
inline uint32_t Payload::_internal_posy() const {
  return posy_;
}
inline uint32_t Payload::posy() const {
  // @@protoc_insertion_point(field_get:rtype.Payload.posY)
  return _internal_posy();
}
inline void Payload::_internal_set_posy(uint32_t value) {
  
  posy_ = value;
}
inline void Payload::set_posy(uint32_t value) {
  _internal_set_posy(value);
  // @@protoc_insertion_point(field_set:rtype.Payload.posY)
}

// uint32 width = 4;
inline void Payload::clear_width() {
  width_ = 0u;
}
inline uint32_t Payload::_internal_width() const {
  return width_;
}
inline uint32_t Payload::width() const {
  // @@protoc_insertion_point(field_get:rtype.Payload.width)
  return _internal_width();
}
inline void Payload::_internal_set_width(uint32_t value) {
  
  width_ = value;
}
inline void Payload::set_width(uint32_t value) {
  _internal_set_width(value);
  // @@protoc_insertion_point(field_set:rtype.Payload.width)
}

// uint32 height = 5;
inline void Payload::clear_height() {
  height_ = 0u;
}
inline uint32_t Payload::_internal_height() const {
  return height_;
}
inline uint32_t Payload::height() const {
  // @@protoc_insertion_point(field_get:rtype.Payload.height)
  return _internal_height();
}
inline void Payload::_internal_set_height(uint32_t value) {
  
  height_ = value;
}
inline void Payload::set_height(uint32_t value) {
  _internal_set_height(value);
  // @@protoc_insertion_point(field_set:rtype.Payload.height)
}

// -------------------------------------------------------------------

// Event

// .rtype.EventType event = 1;
inline void Event::clear_event() {
  event_ = 0;
}
inline ::rtype::EventType Event::_internal_event() const {
  return static_cast< ::rtype::EventType >(event_);
}
inline ::rtype::EventType Event::event() const {
  // @@protoc_insertion_point(field_get:rtype.Event.event)
  return _internal_event();
}
inline void Event::_internal_set_event(::rtype::EventType value) {
  
  event_ = value;
}
inline void Event::set_event(::rtype::EventType value) {
  _internal_set_event(value);
  // @@protoc_insertion_point(field_set:rtype.Event.event)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace rtype

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::rtype::Type> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rtype::Type>() {
  return ::rtype::Type_descriptor();
}
template <> struct is_proto_enum< ::rtype::EventType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rtype::EventType>() {
  return ::rtype::EventType_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_payload_2eproto
