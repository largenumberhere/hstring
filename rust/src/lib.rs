// These exactly match the raw C files
#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

#[cfg(test)]
mod tests{
    use crate::hstring_new;

    #[test]
    fn creation(){
        let hstring  = unsafe{ hstring_new() };
        println!("{:p}",hstring.contents);
    }
}