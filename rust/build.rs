use std::env;
use std::path::PathBuf;

// Runs just before compilation. Any stdout from this is piped into rustc's args
fn main() {

    //Compile the hstring code into a hstring.a and hstring.o library file and place it into `OUT_DIR`
    cc::Build::new()
        .file("hstring.c")
        .compile("hstring");

    println!("cargo:rerun-if-changed=hstring.h");
    // The bindgen::Builder is the main entry point
    // to bindgen, and lets you build up options for
    // the resulting bindings.
    let bindings = bindgen::Builder::default()
        .header("hstring.h")

        // Tell cargo to invalidate the built crate whenever any of the
        // included header files changed.
        .parse_callbacks(Box::new(bindgen::CargoCallbacks))

        // Use the c type aliaes from this package
        .ctypes_prefix("cty")

        // Use the bare bones rust core library which is availible anywhere
        .use_core()

        // Finish the builder and generate the bindings.
        .generate()

        // Unwrap the Result and panic on failure.
        .expect("Unable to generate bindings");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let out_dir = env::var("OUT_DIR").unwrap();
    let out_path = PathBuf::from(&out_dir);
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
    //println!("cargo:warning=Bindings output to: {}/bindings.rs", out_dir);
    //println!("Complete!");
}