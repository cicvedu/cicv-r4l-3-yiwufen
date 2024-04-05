use core::pin::Pin;
use kernel::prelude::*;
use kernel::{chrdev, c_types, file_operations};
use kernel::sync::completion;

struct CompletionDev {
    completion: completion::Completion,
    chrdev: chrdev::Registration,
}

impl CompletionDev {
    fn new() -> Result<Self> {
        let completion = completion::Completion::new();
        let mut chrdev = chrdev::Registration::new_pinned::<Self>(
            cstr!("completion"),
            chrdev::Region::new(),
        )?;

        chrdev.as_mut().register()?;

        Ok(CompletionDev { completion, chrdev })
    }
}

impl file_operations::FileOpener<()> for CompletionDev {
    fn open(ctx: &file_operations::FileOpenContext, file: &kernel::File) -> Result<Self::Wrapper> {
        pr_info!("completion_open is invoked\n");
        Ok(())
    }
}

impl file_operations::FileOperations for CompletionDev {
    fn read(&self, file: &kernel::File, data: &mut kernel::user_ptr::UserSlicePtrWriter, offset: u64) -> Result<usize> {
        pr_info!("completion_read is invoked\n");
        
        // 假设这里我们调用的是一个安全的Rust封装，如果没有，需要使用unsafe代码直接调用
        self.completion.wait();

        pr_info!("awoken\n");
        Ok(0)
    }

    fn write(&self, file: &kernel::File, data: &kernel::user_ptr::UserSlicePtrReader, offset: u64) -> Result<usize> {
        pr_info!("completion_write is invoked\n");
        
        // 同上，我们假设`complete`函数是安全的
        self.completion.complete();

        pr_info!("process awakened\n");
        Ok(0)
    }
}

// Module initialization and cleanup
struct MyModule {
    _dev: Pin<Box<CompletionDev>>,
}

impl KernelModule for MyModule {
    fn init() -> Result<Self> {
        pr_info!("Completion module loaded\n");
        Ok(MyModule {
            _dev: Box::pin(CompletionDev::new()?),
        })
    }
}

impl Drop for MyModule {
    fn drop(&mut self) {
        pr_info!("Completion module unloaded\n");
    }
}

module! {
    type: MyModule,
    name: b"completion",
    author: b"author",
    description: b"Example of Kernel's completion mechanism in Rust",
    license: b"GPL",
}
