print("teest")
local lspconfig = require('lspconfig')
lspconfig.clangd.setup ({
	cmd = { "/opt/esp/tools/esp-clang/esp-18.1.2_20240912/esp-clang/bin/clangd" }
})
