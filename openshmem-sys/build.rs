use std::path::PathBuf;
// use pkg_config::probe_library;

fn main() {
    // let inc_dir = if std::env::var("DOCS_RS").is_ok() {
    //     Some(std::env::var("CARGO_MANIFEST_DIR").unwrap() + "/osss-ucx/include")
    // } else {
    //     std::env::var("SHMEM_INSTALL_DIR").or_else(|_| {
    //         let base_conf = pkg_config::Config::new().atleast_version("1.5");
    //         let known = ["sandia-openshmem", ]
    //     })
    // };
    let inc_dir = if std::env::var("DOCS_RS").is_ok() {
        Some(std::env::var("CARGO_MANIFEST_DIR").unwrap() + "/osss-ucx/include")
    } else {
        std::env::var("SHMEM_INSTALL_DIR").ok()
    };
    let install_dir = inc_dir.expect("SHMEM_INSTALL_DIR must be provided!");
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
