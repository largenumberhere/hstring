// These exactly match the raw C files
#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

#[cfg(test)]
mod tests{
    use crate::hstring_new;
    use crate::hstring_print;

    #[test]
    fn creation(){
        unsafe{
            let mut hstring = hstring_new();
            //hstring_print(&mut hstring);
            let output = format!("{:?}", &hstring);
        }

    }
}