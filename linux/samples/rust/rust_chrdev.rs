// SPDX-License-Identifier: GPL-2.0

//! Rust character device sample.

use core::result::Result::{Err, Ok};

use kernel::prelude::*;
use kernel::sync::Mutex;
use kernel::{chrdev, file};

const GLOBALMEM_SIZE: usize = 0x1000;

module! {
    type: RustChrdev,
    name: "rust_chrdev",
    author: "Rust for Linux Contributors",
    description: "Rust character device sample",
    license: "GPL",
}

static GLOBALMEM_BUF: Mutex<[u8;GLOBALMEM_SIZE]> = unsafe {
    Mutex::new([0u8;GLOBALMEM_SIZE])
};

struct RustFile {
    #[allow(dead_code)]
    inner: &'static Mutex<[u8;GLOBALMEM_SIZE]>,
}

#[vtable]
impl file::Operations for RustFile {
    type Data = Box<Self>;

    fn open(_shared: &(), _file: &file::File) -> Result<Box<Self>> {
        Ok(
            Box::try_new(RustFile {
                inner: &GLOBALMEM_BUF
            })?
        )
    }

    /// 写入函数，用于将数据写入设备
    fn write(_this: &Self, _file: &file::File, _reader: &mut impl kernel::io_buffer::IoBufferReader, _offset: u64) -> Result<usize> {
        let mut buf = _this.inner.lock();
        let len = _reader.len();

        // 根据偏移量调整写入位置
        let offset = _offset as usize;
        let len = core::cmp::min(len, GLOBALMEM_SIZE - offset);
        let data = _reader.read_all()?;
        buf[offset..offset + len].copy_from_slice(&data[..len]);
        Ok(len)
    }

    fn read(_this: &Self,_file: &file::File,_writer: &mut impl kernel::io_buffer::IoBufferWriter,_offset:u64,) -> Result<usize> {
        let buf = _this.inner.lock();
        // 计算可从偏移量开始读取的最大字节数
        let max_readable = GLOBALMEM_SIZE - _offset as usize;
        // 获取实际要读取的数据切片
        let data_to_read = &buf[_offset as usize.._offset as usize + max_readable];
        _writer.write_slice(data_to_read)?;
        Ok(data_to_read.len())
    }
}

struct RustChrdev {
    _dev: Pin<Box<chrdev::Registration<2>>>,
}

impl kernel::Module for RustChrdev {
    fn init(name: &'static CStr, module: &'static ThisModule) -> Result<Self> {
        pr_info!("Rust character device sample (init)\n");

        let mut chrdev_reg = chrdev::Registration::new_pinned(name, 0, module)?;

        // Register the same kind of device twice, we're just demonstrating
        // that you can use multiple minors. There are two minors in this case
        // because its type is `chrdev::Registration<2>`
        chrdev_reg.as_mut().register::<RustFile>()?;
        chrdev_reg.as_mut().register::<RustFile>()?;

        Ok(RustChrdev { _dev: chrdev_reg })
    }
}

impl Drop for RustChrdev {
    fn drop(&mut self) {
        pr_info!("Rust character device sample (exit)\n");
    }
}
