// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: enemies.proto
// Protobuf C++ Version: 5.29.2

#ifndef enemies_2eproto_2epb_2eh
#define enemies_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/runtime_version.h"
#if PROTOBUF_VERSION != 5029001
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/message_lite.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_enemies_2eproto

namespace google {
namespace protobuf {
namespace internal {
template <typename T>
::absl::string_view GetAnyMessageName();
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_enemies_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_enemies_2eproto;
class Enemies;
struct EnemiesDefaultTypeInternal;
extern EnemiesDefaultTypeInternal _Enemies_default_instance_;
class EnemyValue;
struct EnemyValueDefaultTypeInternal;
extern EnemyValueDefaultTypeInternal _EnemyValue_default_instance_;
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google


// ===================================================================


// -------------------------------------------------------------------

class EnemyValue final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:EnemyValue) */ {
 public:
  inline EnemyValue() : EnemyValue(nullptr) {}
  ~EnemyValue() PROTOBUF_FINAL;

#if defined(PROTOBUF_CUSTOM_VTABLE)
  void operator delete(EnemyValue* msg, std::destroying_delete_t) {
    SharedDtor(*msg);
    ::google::protobuf::internal::SizedDelete(msg, sizeof(EnemyValue));
  }
#endif

  template <typename = void>
  explicit PROTOBUF_CONSTEXPR EnemyValue(
      ::google::protobuf::internal::ConstantInitialized);

  inline EnemyValue(const EnemyValue& from) : EnemyValue(nullptr, from) {}
  inline EnemyValue(EnemyValue&& from) noexcept
      : EnemyValue(nullptr, std::move(from)) {}
  inline EnemyValue& operator=(const EnemyValue& from) {
    CopyFrom(from);
    return *this;
  }
  inline EnemyValue& operator=(EnemyValue&& from) noexcept {
    if (this == &from) return *this;
    if (::google::protobuf::internal::CanMoveWithInternalSwap(GetArena(), from.GetArena())) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const EnemyValue& default_instance() {
    return *internal_default_instance();
  }
  static inline const EnemyValue* internal_default_instance() {
    return reinterpret_cast<const EnemyValue*>(
        &_EnemyValue_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(EnemyValue& a, EnemyValue& b) { a.Swap(&b); }
  inline void Swap(EnemyValue* other) {
    if (other == this) return;
    if (::google::protobuf::internal::CanUseInternalSwap(GetArena(), other->GetArena())) {
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(EnemyValue* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  EnemyValue* New(::google::protobuf::Arena* arena = nullptr) const {
    return ::google::protobuf::Message::DefaultConstruct<EnemyValue>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const EnemyValue& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const EnemyValue& from) { EnemyValue::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  static void SharedDtor(MessageLite& self);
  void InternalSwap(EnemyValue* other);
 private:
  template <typename T>
  friend ::absl::string_view(
      ::google::protobuf::internal::GetAnyMessageName)();
  static ::absl::string_view FullMessageName() { return "EnemyValue"; }

 protected:
  explicit EnemyValue(::google::protobuf::Arena* arena);
  EnemyValue(::google::protobuf::Arena* arena, const EnemyValue& from);
  EnemyValue(::google::protobuf::Arena* arena, EnemyValue&& from) noexcept
      : EnemyValue(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::internal::ClassData* GetClassData() const PROTOBUF_FINAL;
  static void* PlacementNew_(const void*, void* mem,
                             ::google::protobuf::Arena* arena);
  static constexpr auto InternalNewImpl_();
  static const ::google::protobuf::internal::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kTeamFieldNumber = 1,
    kNameFieldNumber = 2,
    kXFieldNumber = 3,
    kYFieldNumber = 4,
    kZFieldNumber = 5,
    kHpFieldNumber = 6,
    kYawFieldNumber = 8,
    kHasDefuseFieldNumber = 7,
    kIsDefusingFieldNumber = 10,
    kPitchFieldNumber = 9,
    kTimeLeftDefuseFieldNumber = 11,
    kTimeLeftExplosionFieldNumber = 12,
  };
  // string team = 1;
  void clear_team() ;
  const std::string& team() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_team(Arg_&& arg, Args_... args);
  std::string* mutable_team();
  PROTOBUF_NODISCARD std::string* release_team();
  void set_allocated_team(std::string* value);

  private:
  const std::string& _internal_team() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_team(
      const std::string& value);
  std::string* _internal_mutable_team();

  public:
  // string name = 2;
  void clear_name() ;
  const std::string& name() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_name(Arg_&& arg, Args_... args);
  std::string* mutable_name();
  PROTOBUF_NODISCARD std::string* release_name();
  void set_allocated_name(std::string* value);

  private:
  const std::string& _internal_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_name(
      const std::string& value);
  std::string* _internal_mutable_name();

  public:
  // float x = 3;
  void clear_x() ;
  float x() const;
  void set_x(float value);

  private:
  float _internal_x() const;
  void _internal_set_x(float value);

  public:
  // float y = 4;
  void clear_y() ;
  float y() const;
  void set_y(float value);

  private:
  float _internal_y() const;
  void _internal_set_y(float value);

  public:
  // float z = 5;
  void clear_z() ;
  float z() const;
  void set_z(float value);

  private:
  float _internal_z() const;
  void _internal_set_z(float value);

  public:
  // int32 hp = 6;
  void clear_hp() ;
  ::int32_t hp() const;
  void set_hp(::int32_t value);

  private:
  ::int32_t _internal_hp() const;
  void _internal_set_hp(::int32_t value);

  public:
  // float yaw = 8;
  void clear_yaw() ;
  float yaw() const;
  void set_yaw(float value);

  private:
  float _internal_yaw() const;
  void _internal_set_yaw(float value);

  public:
  // bool has_defuse = 7;
  void clear_has_defuse() ;
  bool has_defuse() const;
  void set_has_defuse(bool value);

  private:
  bool _internal_has_defuse() const;
  void _internal_set_has_defuse(bool value);

  public:
  // bool is_defusing = 10;
  void clear_is_defusing() ;
  bool is_defusing() const;
  void set_is_defusing(bool value);

  private:
  bool _internal_is_defusing() const;
  void _internal_set_is_defusing(bool value);

  public:
  // float pitch = 9;
  void clear_pitch() ;
  float pitch() const;
  void set_pitch(float value);

  private:
  float _internal_pitch() const;
  void _internal_set_pitch(float value);

  public:
  // float time_left_defuse = 11;
  void clear_time_left_defuse() ;
  float time_left_defuse() const;
  void set_time_left_defuse(float value);

  private:
  float _internal_time_left_defuse() const;
  void _internal_set_time_left_defuse(float value);

  public:
  // float time_left_explosion = 12;
  void clear_time_left_explosion() ;
  float time_left_explosion() const;
  void set_time_left_explosion(float value);

  private:
  float _internal_time_left_explosion() const;
  void _internal_set_time_left_explosion(float value);

  public:
  // @@protoc_insertion_point(class_scope:EnemyValue)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      4, 12, 0,
      35, 2>
      _table_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const EnemyValue& from_msg);
    ::google::protobuf::internal::ArenaStringPtr team_;
    ::google::protobuf::internal::ArenaStringPtr name_;
    float x_;
    float y_;
    float z_;
    ::int32_t hp_;
    float yaw_;
    bool has_defuse_;
    bool is_defusing_;
    float pitch_;
    float time_left_defuse_;
    float time_left_explosion_;
    ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_enemies_2eproto;
};
// -------------------------------------------------------------------

class Enemies final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:Enemies) */ {
 public:
  inline Enemies() : Enemies(nullptr) {}
  ~Enemies() PROTOBUF_FINAL;

#if defined(PROTOBUF_CUSTOM_VTABLE)
  void operator delete(Enemies* msg, std::destroying_delete_t) {
    SharedDtor(*msg);
    ::google::protobuf::internal::SizedDelete(msg, sizeof(Enemies));
  }
#endif

  template <typename = void>
  explicit PROTOBUF_CONSTEXPR Enemies(
      ::google::protobuf::internal::ConstantInitialized);

  inline Enemies(const Enemies& from) : Enemies(nullptr, from) {}
  inline Enemies(Enemies&& from) noexcept
      : Enemies(nullptr, std::move(from)) {}
  inline Enemies& operator=(const Enemies& from) {
    CopyFrom(from);
    return *this;
  }
  inline Enemies& operator=(Enemies&& from) noexcept {
    if (this == &from) return *this;
    if (::google::protobuf::internal::CanMoveWithInternalSwap(GetArena(), from.GetArena())) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Enemies& default_instance() {
    return *internal_default_instance();
  }
  static inline const Enemies* internal_default_instance() {
    return reinterpret_cast<const Enemies*>(
        &_Enemies_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(Enemies& a, Enemies& b) { a.Swap(&b); }
  inline void Swap(Enemies* other) {
    if (other == this) return;
    if (::google::protobuf::internal::CanUseInternalSwap(GetArena(), other->GetArena())) {
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Enemies* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Enemies* New(::google::protobuf::Arena* arena = nullptr) const {
    return ::google::protobuf::Message::DefaultConstruct<Enemies>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const Enemies& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const Enemies& from) { Enemies::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  static void SharedDtor(MessageLite& self);
  void InternalSwap(Enemies* other);
 private:
  template <typename T>
  friend ::absl::string_view(
      ::google::protobuf::internal::GetAnyMessageName)();
  static ::absl::string_view FullMessageName() { return "Enemies"; }

 protected:
  explicit Enemies(::google::protobuf::Arena* arena);
  Enemies(::google::protobuf::Arena* arena, const Enemies& from);
  Enemies(::google::protobuf::Arena* arena, Enemies&& from) noexcept
      : Enemies(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::internal::ClassData* GetClassData() const PROTOBUF_FINAL;
  static void* PlacementNew_(const void*, void* mem,
                             ::google::protobuf::Arena* arena);
  static constexpr auto InternalNewImpl_();
  static const ::google::protobuf::internal::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kEntriesFieldNumber = 1,
  };
  // repeated .EnemyValue entries = 1;
  int entries_size() const;
  private:
  int _internal_entries_size() const;

  public:
  void clear_entries() ;
  ::EnemyValue* mutable_entries(int index);
  ::google::protobuf::RepeatedPtrField<::EnemyValue>* mutable_entries();

  private:
  const ::google::protobuf::RepeatedPtrField<::EnemyValue>& _internal_entries() const;
  ::google::protobuf::RepeatedPtrField<::EnemyValue>* _internal_mutable_entries();
  public:
  const ::EnemyValue& entries(int index) const;
  ::EnemyValue* add_entries();
  const ::google::protobuf::RepeatedPtrField<::EnemyValue>& entries() const;
  // @@protoc_insertion_point(class_scope:Enemies)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 1,
      0, 2>
      _table_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const Enemies& from_msg);
    ::google::protobuf::RepeatedPtrField< ::EnemyValue > entries_;
    ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_enemies_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// EnemyValue

// string team = 1;
inline void EnemyValue::clear_team() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.team_.ClearToEmpty();
}
inline const std::string& EnemyValue::team() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:EnemyValue.team)
  return _internal_team();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void EnemyValue::set_team(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.team_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:EnemyValue.team)
}
inline std::string* EnemyValue::mutable_team() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_team();
  // @@protoc_insertion_point(field_mutable:EnemyValue.team)
  return _s;
}
inline const std::string& EnemyValue::_internal_team() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.team_.Get();
}
inline void EnemyValue::_internal_set_team(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.team_.Set(value, GetArena());
}
inline std::string* EnemyValue::_internal_mutable_team() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.team_.Mutable( GetArena());
}
inline std::string* EnemyValue::release_team() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:EnemyValue.team)
  return _impl_.team_.Release();
}
inline void EnemyValue::set_allocated_team(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.team_.SetAllocated(value, GetArena());
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString() && _impl_.team_.IsDefault()) {
    _impl_.team_.Set("", GetArena());
  }
  // @@protoc_insertion_point(field_set_allocated:EnemyValue.team)
}

// string name = 2;
inline void EnemyValue::clear_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.name_.ClearToEmpty();
}
inline const std::string& EnemyValue::name() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:EnemyValue.name)
  return _internal_name();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void EnemyValue::set_name(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.name_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:EnemyValue.name)
}
inline std::string* EnemyValue::mutable_name() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:EnemyValue.name)
  return _s;
}
inline const std::string& EnemyValue::_internal_name() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.name_.Get();
}
inline void EnemyValue::_internal_set_name(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.name_.Set(value, GetArena());
}
inline std::string* EnemyValue::_internal_mutable_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.name_.Mutable( GetArena());
}
inline std::string* EnemyValue::release_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:EnemyValue.name)
  return _impl_.name_.Release();
}
inline void EnemyValue::set_allocated_name(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.name_.SetAllocated(value, GetArena());
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString() && _impl_.name_.IsDefault()) {
    _impl_.name_.Set("", GetArena());
  }
  // @@protoc_insertion_point(field_set_allocated:EnemyValue.name)
}

// float x = 3;
inline void EnemyValue::clear_x() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.x_ = 0;
}
inline float EnemyValue::x() const {
  // @@protoc_insertion_point(field_get:EnemyValue.x)
  return _internal_x();
}
inline void EnemyValue::set_x(float value) {
  _internal_set_x(value);
  // @@protoc_insertion_point(field_set:EnemyValue.x)
}
inline float EnemyValue::_internal_x() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.x_;
}
inline void EnemyValue::_internal_set_x(float value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.x_ = value;
}

// float y = 4;
inline void EnemyValue::clear_y() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.y_ = 0;
}
inline float EnemyValue::y() const {
  // @@protoc_insertion_point(field_get:EnemyValue.y)
  return _internal_y();
}
inline void EnemyValue::set_y(float value) {
  _internal_set_y(value);
  // @@protoc_insertion_point(field_set:EnemyValue.y)
}
inline float EnemyValue::_internal_y() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.y_;
}
inline void EnemyValue::_internal_set_y(float value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.y_ = value;
}

// float z = 5;
inline void EnemyValue::clear_z() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.z_ = 0;
}
inline float EnemyValue::z() const {
  // @@protoc_insertion_point(field_get:EnemyValue.z)
  return _internal_z();
}
inline void EnemyValue::set_z(float value) {
  _internal_set_z(value);
  // @@protoc_insertion_point(field_set:EnemyValue.z)
}
inline float EnemyValue::_internal_z() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.z_;
}
inline void EnemyValue::_internal_set_z(float value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.z_ = value;
}

// int32 hp = 6;
inline void EnemyValue::clear_hp() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.hp_ = 0;
}
inline ::int32_t EnemyValue::hp() const {
  // @@protoc_insertion_point(field_get:EnemyValue.hp)
  return _internal_hp();
}
inline void EnemyValue::set_hp(::int32_t value) {
  _internal_set_hp(value);
  // @@protoc_insertion_point(field_set:EnemyValue.hp)
}
inline ::int32_t EnemyValue::_internal_hp() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.hp_;
}
inline void EnemyValue::_internal_set_hp(::int32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.hp_ = value;
}

// float yaw = 8;
inline void EnemyValue::clear_yaw() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.yaw_ = 0;
}
inline float EnemyValue::yaw() const {
  // @@protoc_insertion_point(field_get:EnemyValue.yaw)
  return _internal_yaw();
}
inline void EnemyValue::set_yaw(float value) {
  _internal_set_yaw(value);
  // @@protoc_insertion_point(field_set:EnemyValue.yaw)
}
inline float EnemyValue::_internal_yaw() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.yaw_;
}
inline void EnemyValue::_internal_set_yaw(float value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.yaw_ = value;
}

// float pitch = 9;
inline void EnemyValue::clear_pitch() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.pitch_ = 0;
}
inline float EnemyValue::pitch() const {
  // @@protoc_insertion_point(field_get:EnemyValue.pitch)
  return _internal_pitch();
}
inline void EnemyValue::set_pitch(float value) {
  _internal_set_pitch(value);
  // @@protoc_insertion_point(field_set:EnemyValue.pitch)
}
inline float EnemyValue::_internal_pitch() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.pitch_;
}
inline void EnemyValue::_internal_set_pitch(float value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.pitch_ = value;
}

// bool has_defuse = 7;
inline void EnemyValue::clear_has_defuse() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.has_defuse_ = false;
}
inline bool EnemyValue::has_defuse() const {
  // @@protoc_insertion_point(field_get:EnemyValue.has_defuse)
  return _internal_has_defuse();
}
inline void EnemyValue::set_has_defuse(bool value) {
  _internal_set_has_defuse(value);
  // @@protoc_insertion_point(field_set:EnemyValue.has_defuse)
}
inline bool EnemyValue::_internal_has_defuse() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.has_defuse_;
}
inline void EnemyValue::_internal_set_has_defuse(bool value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.has_defuse_ = value;
}

// bool is_defusing = 10;
inline void EnemyValue::clear_is_defusing() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.is_defusing_ = false;
}
inline bool EnemyValue::is_defusing() const {
  // @@protoc_insertion_point(field_get:EnemyValue.is_defusing)
  return _internal_is_defusing();
}
inline void EnemyValue::set_is_defusing(bool value) {
  _internal_set_is_defusing(value);
  // @@protoc_insertion_point(field_set:EnemyValue.is_defusing)
}
inline bool EnemyValue::_internal_is_defusing() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.is_defusing_;
}
inline void EnemyValue::_internal_set_is_defusing(bool value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.is_defusing_ = value;
}

// float time_left_defuse = 11;
inline void EnemyValue::clear_time_left_defuse() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.time_left_defuse_ = 0;
}
inline float EnemyValue::time_left_defuse() const {
  // @@protoc_insertion_point(field_get:EnemyValue.time_left_defuse)
  return _internal_time_left_defuse();
}
inline void EnemyValue::set_time_left_defuse(float value) {
  _internal_set_time_left_defuse(value);
  // @@protoc_insertion_point(field_set:EnemyValue.time_left_defuse)
}
inline float EnemyValue::_internal_time_left_defuse() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.time_left_defuse_;
}
inline void EnemyValue::_internal_set_time_left_defuse(float value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.time_left_defuse_ = value;
}

// float time_left_explosion = 12;
inline void EnemyValue::clear_time_left_explosion() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.time_left_explosion_ = 0;
}
inline float EnemyValue::time_left_explosion() const {
  // @@protoc_insertion_point(field_get:EnemyValue.time_left_explosion)
  return _internal_time_left_explosion();
}
inline void EnemyValue::set_time_left_explosion(float value) {
  _internal_set_time_left_explosion(value);
  // @@protoc_insertion_point(field_set:EnemyValue.time_left_explosion)
}
inline float EnemyValue::_internal_time_left_explosion() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.time_left_explosion_;
}
inline void EnemyValue::_internal_set_time_left_explosion(float value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.time_left_explosion_ = value;
}

// -------------------------------------------------------------------

// Enemies

// repeated .EnemyValue entries = 1;
inline int Enemies::_internal_entries_size() const {
  return _internal_entries().size();
}
inline int Enemies::entries_size() const {
  return _internal_entries_size();
}
inline void Enemies::clear_entries() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.entries_.Clear();
}
inline ::EnemyValue* Enemies::mutable_entries(int index)
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable:Enemies.entries)
  return _internal_mutable_entries()->Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField<::EnemyValue>* Enemies::mutable_entries()
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable_list:Enemies.entries)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _internal_mutable_entries();
}
inline const ::EnemyValue& Enemies::entries(int index) const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Enemies.entries)
  return _internal_entries().Get(index);
}
inline ::EnemyValue* Enemies::add_entries() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::EnemyValue* _add = _internal_mutable_entries()->Add();
  // @@protoc_insertion_point(field_add:Enemies.entries)
  return _add;
}
inline const ::google::protobuf::RepeatedPtrField<::EnemyValue>& Enemies::entries() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_list:Enemies.entries)
  return _internal_entries();
}
inline const ::google::protobuf::RepeatedPtrField<::EnemyValue>&
Enemies::_internal_entries() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.entries_;
}
inline ::google::protobuf::RepeatedPtrField<::EnemyValue>*
Enemies::_internal_mutable_entries() {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return &_impl_.entries_;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // enemies_2eproto_2epb_2eh