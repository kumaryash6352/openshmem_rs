

fn main() {
    let i = 2;
    {
        let mut x = 3;
        let y: &usize = &x;


        x = 5;

    }

    dbg!(y);
}
