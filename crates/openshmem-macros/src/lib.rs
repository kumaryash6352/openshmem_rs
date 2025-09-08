// A type may derive Shend iff:
// 1. All types it contains are Shend.
//
// Seriously. That's it.
//
// We manually implement Shend on known safe PGAS types.
//
// 1. [u/i][1..64]
// 2. [u/i]size
// 3. f32, f64
// 4. char
// 5. Atomic (which is also Shync)
// 6. Option<impl Shend>
// 7. Result<impl Shend, impl Shend>
// 8. (impl Shend, impl Shend, ..)


extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, Data, DeriveInput, Fields};

#[proc_macro_derive(Shend)]
pub fn shend_derive(input: TokenStream) -> TokenStream {
    let input = parse_macro_input!(input as DeriveInput);

    let name = input.ident;


    let generics = &input.generics;
    let (impl_generics, ty_generics, where_clause) = generics.split_for_impl();

    let mut where_predicates = Vec::new();

    match input.data {
        Data::Struct(data_struct) => {
            match data_struct.fields {
                Fields::Named(fields) => {
                    for field in fields.named {
                        let ty = &field.ty;
                        where_predicates.push(quote! { #ty: Shend });
                    }
                }
                Fields::Unnamed(fields) => {
                    for field in fields.unnamed {
                        let ty = &field.ty;
                        where_predicates.push(quote! { #ty: Shend });
                    }
                }
                Fields::Unit => {
                    // trivially satisfies Shend
                }
            }
        }
        Data::Enum(data_enum) => {
            for variant in data_enum.variants {
                match variant.fields {
                    Fields::Named(fields) => {
                        for field in fields.named {
                            let ty = &field.ty;
                            where_predicates.push(quote! { #ty: Shend });
                        }
                    }
                    Fields::Unnamed(fields) => {
                        for field in fields.unnamed {
                            let ty = &field.ty;
                            where_predicates.push(quote! { #ty: Shend });
                        }
                    }
                    Fields::Unit => {
                        // trivially satisfies Shend
                    }
                }
            }
        }
        Data::Union(_) => {
            // so, unions.
            // frankly, i'm not too sure what to do here.
            // unions are unsafe on their own, so unsafe impl Shend
            // could apply.
            return syn::Error::new_spanned(
                name,
                "Shend must be manually implemented for Unions.",
            )
            .to_compile_error()
            .into();
        }
    };

    let existing_where_clause = where_clause.map_or(quote!{}, |clause| quote!{ #clause });

    let new_where_clause = if where_predicates.is_empty() {
        quote! { #existing_where_clause }
    } else {
        quote! { #existing_where_clause #(#where_predicates),* }
    };

    let final_where_clause = if new_where_clause.is_empty() {
        quote!{}
    } else {
        quote!{ where #new_where_clause }
    };


    let generated_impl = quote! {
        unsafe impl #impl_generics Shend for #name #ty_generics #final_where_clause {}
    };

    TokenStream::from(generated_impl)
}
