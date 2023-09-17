/* automatically generated by rust-bindgen 0.65.1 */

pub type wchar_t = ::std::os::raw::c_int;
#[repr(C)]
#[repr(align(16))]
#[derive(Debug, Copy, Clone)]
pub struct max_align_t {
    pub __clang_max_align_nonce1: ::std::os::raw::c_longlong,
    pub __bindgen_padding_0: u64,
    pub __clang_max_align_nonce2: u128,
}
#[test]
fn bindgen_test_layout_max_align_t() {
    const UNINIT: ::std::mem::MaybeUninit<max_align_t> = ::std::mem::MaybeUninit::uninit();
    let ptr = UNINIT.as_ptr();
    assert_eq!(
        ::std::mem::size_of::<max_align_t>(),
        32usize,
        concat!("Size of: ", stringify!(max_align_t))
    );
    assert_eq!(
        ::std::mem::align_of::<max_align_t>(),
        16usize,
        concat!("Alignment of ", stringify!(max_align_t))
    );
    assert_eq!(
        unsafe { ::std::ptr::addr_of!((*ptr).__clang_max_align_nonce1) as usize - ptr as usize },
        0usize,
        concat!(
            "Offset of field: ",
            stringify!(max_align_t),
            "::",
            stringify!(__clang_max_align_nonce1)
        )
    );
    assert_eq!(
        unsafe { ::std::ptr::addr_of!((*ptr).__clang_max_align_nonce2) as usize - ptr as usize },
        16usize,
        concat!(
            "Offset of field: ",
            stringify!(max_align_t),
            "::",
            stringify!(__clang_max_align_nonce2)
        )
    );
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct HSTRING {
    pub capacity: usize,
    pub length: usize,
    pub contents: *mut ::std::os::raw::c_char,
}
#[test]
fn bindgen_test_layout_HSTRING() {
    const UNINIT: ::std::mem::MaybeUninit<HSTRING> = ::std::mem::MaybeUninit::uninit();
    let ptr = UNINIT.as_ptr();
    assert_eq!(
        ::std::mem::size_of::<HSTRING>(),
        24usize,
        concat!("Size of: ", stringify!(HSTRING))
    );
    assert_eq!(
        ::std::mem::align_of::<HSTRING>(),
        8usize,
        concat!("Alignment of ", stringify!(HSTRING))
    );
    assert_eq!(
        unsafe { ::std::ptr::addr_of!((*ptr).capacity) as usize - ptr as usize },
        0usize,
        concat!(
            "Offset of field: ",
            stringify!(HSTRING),
            "::",
            stringify!(capacity)
        )
    );
    assert_eq!(
        unsafe { ::std::ptr::addr_of!((*ptr).length) as usize - ptr as usize },
        8usize,
        concat!(
            "Offset of field: ",
            stringify!(HSTRING),
            "::",
            stringify!(length)
        )
    );
    assert_eq!(
        unsafe { ::std::ptr::addr_of!((*ptr).contents) as usize - ptr as usize },
        16usize,
        concat!(
            "Offset of field: ",
            stringify!(HSTRING),
            "::",
            stringify!(contents)
        )
    );
}
extern "C" {
    pub fn hstring_new() -> HSTRING;
}
extern "C" {
    pub fn hstring_new_with(capacity: ::std::os::raw::c_int) -> HSTRING;
}
extern "C" {
    pub fn hstring_push_char(hstring: *mut HSTRING, item: ::std::os::raw::c_char);
}
extern "C" {
    pub fn hstring_push_string(
        hstring: *mut HSTRING,
        null_terminated_string: *mut ::std::os::raw::c_char,
    );
}
extern "C" {
    pub fn hstring_push_string_raw(
        hstring: *mut HSTRING,
        unterminated_string: *mut ::std::os::raw::c_char,
        string_length_excluding_terminator: ::std::os::raw::c_int,
    );
}
extern "C" {
    pub fn hstring_read_stdin_char(hstring: *mut HSTRING);
}
extern "C" {
    pub fn hstring_read_stdin_line(hstring: *mut HSTRING);
}
extern "C" {
    pub fn hstring_clear(hstring: *mut HSTRING);
}
extern "C" {
    pub fn hstring_free(hstring: *mut HSTRING);
}
extern "C" {
    pub fn hstring_print(hstring: *mut HSTRING);
}
extern "C" {
    pub fn hstring_validity_assert(hstring: *mut HSTRING, messagem: *const ::std::os::raw::c_char);
}
extern "C" {
    pub fn hstring_get_int(hstring: *mut HSTRING) -> ::std::os::raw::c_int;
}