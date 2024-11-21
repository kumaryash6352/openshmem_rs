use std::path::PathBuf;

fn main() {
    let install_dir = if std::env::var("DOCS_RS").is_ok() {
        std::env::var("CARGO_MANIFEST_DIR").unwrap() + "/osss-ucx"
    } else {
        std::env::var("SHMEM_INSTALL_DIR").expect("SHMEM_INSTALL_DIR to be provided!")
    };
    println!("cargo:rustc-link-search={install_dir}/lib");
    println!("cargo:rustc-link-lib=sma");
    println!("cargo:rustc-link-lib=pmi_simple");
    let out = PathBuf::from(std::env::var("OUT_DIR").unwrap());
    for header in [
        "shmem",
        #[cfg(feature = "shmemx")]
        "shmemx",
    ] {
        let bindings = bindgen::Builder::default()
            .header(&format!("{install_dir}/include/{header}.h"))
            .clang_arg(format!("-I{install_dir}/include"))
            .parse_callbacks(Box::new(bindgen::CargoCallbacks::new()))
            .generate()
            .expect(&format!("generating {header}.h bindings"));

        bindings
            .write_to_file(out.join(format!("{header}_bindings.rs")))
            .expect(&format!("writing {header}.h bindings"));
    }
}
