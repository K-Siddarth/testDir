vim.g.mapleader = ' '

-- Ensure that packer.nvim is installed automatically if it’s not already
local function ensure_packer()
    local fn = vim.fn
    local install_path = fn.stdpath('data')..'/site/pack/packer/start/packer.nvim'
    if fn.empty(fn.glob(install_path)) > 0 then
        fn.system({
            'git', 'clone', '--depth', '1',
            'https://github.com/wbthomason/packer.nvim', install_path
        })
        vim.cmd('packadd packer.nvim')
    end
end

ensure_packer()

-- Automatically source and recompile packer whenever plugins.lua is updated
vim.cmd([[
  augroup packer_user_config
  autocmd!
  autocmd BufWritePost init.lua source <afile> | PackerCompile
  augroup end
]])

-- Packer plugin manager
require('packer').startup(function(use)
    use 'wbthomason/packer.nvim' -- Manage packer itself

    use {
        'windwp/nvim-autopairs',
        config = function()
            require('nvim-autopairs').setup({
                opts = {
                    enable_close = true, -- Enable auto-closing for all tags
                    enable_rename = true, -- Enable auto-rename for pairs of tags
                    enable_close_on_slash = false, -- Disable closing tag on trailing slash </>
                },
                per_filetype = {
                    ["html"] = {
                        enable_close = true  -- Enable auto-close for HTML
                    },
                    ["javascript"] = {
                        enable_close = true  -- Enable auto-close for JSX inside JavaScript files
                    },
                },
                check_ts = true  -- Enable Treesitter support for JavaScript (includes JSX)
            })
        end
    }
    -- Fuzzy Finder
    use 'nvim-lua/plenary.nvim' -- Dependency for Telescope
    use {
        'nvim-telescope/telescope.nvim',
        tag = '0.1.2',
        requires = { {'nvim-lua/plenary.nvim'} }
    }

    -- Harpoon
    use 'ThePrimeagen/harpoon'

    -- Navigation Plugins
    use 'rbgrouleff/bclose.vim'
    use 'scrooloose/nerdtree'


    -- UI Plugins
    use 'vim-airline/vim-airline'
    use 'vim-airline/vim-airline-themes'
    use 'bling/vim-bufferline'
    use 'altercation/vim-colors-solarized'
    use 'ishan9299/nvim-solarized-lua'
    use 'rose-pine/neovim'


    -- Editing Experience
    use 'Raimondi/delimitMate'
    use 'scrooloose/nerdcommenter'
    use 'tpope/vim-sleuth'
    use 'airblade/vim-gitgutter'
    use 'editorconfig/editorconfig-vim'

    -- File Search & Navigation
    use 'junegunn/fzf'
    use 'junegunn/fzf.vim'

    -- Commenting plugin
    use 'numToStr/Comment.nvim'

    -- LSP, Treesitter, and Autocompletion
    use 'neovim/nvim-lspconfig'
    use {'nvim-treesitter/nvim-treesitter', run = ':TSUpdate'}
    use 'nvim-treesitter/playground'
    use 'hrsh7th/nvim-cmp'
    use 'hrsh7th/cmp-buffer'
    use 'hrsh7th/cmp-path'
    use 'hrsh7th/cmp-cmdline'
    use 'hrsh7th/cmp-nvim-lsp'
    use 'hrsh7th/cmp-vsnip'
    use 'hrsh7th/vim-vsnip'

    -- Git Integration
    use 'tpope/vim-fugitive'

    -- AI-powered coding assistant
    use 'Exafunction/codeium.vim'

    -- Language Specific Plugins
    use {'lervag/vimtex', ft = 'tex'}
    use 'vim-pandoc/vim-pandoc'
    use 'Vimjas/vim-python-pep8-indent'
    use 'maxmellon/vim-jsx-pretty'
    use 'iden3/vim-circom-syntax'
    use 'tmhedberg/SimpylFold'

    -- Note-taking
    use 'lukaszkorecki/workflowish'

    -- multi line Editing
    use 'mg979/vim-visual-multi'

    -- idk what is am doing
    use {'neoclide/coc.nvim', branch = 'release'}
end)
-- Basic settings
vim.opt.number = true  -- Enable line numbers
vim.opt.relativenumber = true  -- Relative line numbers
vim.opt.expandtab = true  -- Use spaces instead of tabs
vim.opt.shiftwidth = 4  -- Shift 2 spaces when tab
vim.opt.tabstop = 4  -- 1 tab == 2 spaces
vim.opt.smartindent = true  -- Autoindent new lines
vim.opt.wrap = false  -- Don't wrap long lines
vim.opt.termguicolors = true  -- Enable 24-bit RGB colors
vim.opt.scrolloff = 8  -- Minimum lines to keep above and below cursor
vim.opt.sidescrolloff = 8  -- Minimum columns to keep to the left and right of cursor
vim.opt.hlsearch = true  -- Highlight search results
vim.opt.incsearch = true  -- Show search matches while typing

-- Airline config
vim.g.airline_theme = 'solarized'
vim.g.airline_powerline_fonts = 1

-- NERDTree configuration
vim.g.NERDTreeShowHidden = 1

-- Bufferline
vim.g.bufferline_echo = 0

-- DelimitMate
vim.g.delimitMate_expand_cr = 1
vim.g.delimitMate_expand_space = 1

-- Auto-commenting
require('Comment').setup()

-- Treesitter configuration
require'nvim-treesitter.configs'.setup {
    ensure_installed = { "bash", "c", "cpp", "html", "javascript", "json", "lua", "python", "typescript", "css", "tsx",},
    auto_install = true,
    highlight = {
        enable = true,
    },
    indent = {
        enable = true
    },
    auto_tag = {
        enable = true
    }
}

-- LSP configuration for multiple languages
local lspconfig = require('lspconfig')
local on_attach = function(_, bufnr)
    local opts = { noremap=true, silent=true }
    local buf_set_keymap = function(...) vim.api.nvim_buf_set_keymap(bufnr, ...) end
    buf_set_keymap('n', 'gd', '<Cmd>lua vim.lsp.buf.definition()<CR>', opts)
    buf_set_keymap('n', 'K', '<Cmd>lua vim.lsp.buf.hover()<CR>', opts)
    buf_set_keymap('n', 'gi', '<cmd>lua vim.lsp.buf.implementation()<CR>', opts)
    buf_set_keymap('n', '<C-y>', '<cmd>lua vim.lsp.buf.signature_help()<CR>', opts)
end

lspconfig.pyright.setup{ on_attach = on_attach }
--lspconfig.tsserver.setup{ on_attach = on_attach }
lspconfig.clangd.setup{ on_attach = on_attach }

-- Autocompletion setup
local cmp = require'cmp'
cmp.setup({
    snippet = {
        expand = function(args)
            vim.fn["vsnip#anonymous"](args.body) -- For `vsnip` users.
        end,
    },
    mapping = {
        ['<C-n>'] = cmp.mapping.select_next_item({ behavior = cmp.SelectBehavior.Insert }),
        ['<C-p>'] = cmp.mapping.select_prev_item({ behavior = cmp.SelectBehavior.Insert }),
        ['<C-d>'] = cmp.mapping.scroll_docs(-4),
        ['<C-f>'] = cmp.mapping.scroll_docs(4),
        ['<C-Space>'] = cmp.mapping.complete(),
        ['<C-e>'] = cmp.mapping.close(),
        ['<CR>'] = cmp.mapping.confirm({
            behavior = cmp.ConfirmBehavior.Replace,
            select = true,
        }),
    },
    sources = cmp.config.sources({
        { name = 'nvim_lsp' },
        { name = 'vsnip' },
        { name = 'buffer' },
        { name = 'path' },
    })
})

-- Fugitive plugin for Git
vim.cmd([[
  nnoremap <leader>gs :G<CR>
  ]])

-- Pandoc key mappings
vim.cmd([[
  nnoremap <leader>pp :Pandoc pdf<CR>
  ]])

-- Workflowish for todo notes
vim.cmd([[
  nnoremap <leader>tw :WorkflowishToggle<CR>
  ]])

-- Codeium AI configuration
vim.cmd([[
  nnoremap <leader>ai :Codeium Toggle<CR>
  ]])

-- Other key mappings
vim.cmd([[
  nnoremap <leader>w :w<CR>
  nnoremap <leader>q :q<CR>
  nnoremap <leader>f :FZF<CR>
  nnoremap <leader>nt :NERDTreeToggle<CR>
  ]])

--clipboard
vim.opt.clipboard:append("unnamedplus")

-- Auto command for C++ file type
-- Auto command for C++ file type
vim.api.nvim_create_autocmd("FileType", {
    pattern = "cpp",
    callback = function()
        -- Map F2 to compile and run the code in a terminal split
        vim.api.nvim_set_keymap('n', '<F2>', ':w<CR>:term!g++ % -o %:r && ./%:r<CR>', { noremap = true, silent = true })
    end,
})

vim.api.nvim_create_autocmd("FileType", {
    pattern = "c",
    callback = function()
        -- Map F2 to compile and run the code in a terminal split
        vim.api.nvim_set_keymap('n', '<F2>', ':w<CR>:term!gcc % -o %:r && ./%:r<CR>', { noremap = true, silent = true })
    end,
})

-- for python files
vim.api.nvim_create_autocmd("FileType", {
    pattern = "py",
    callback = function()
        -- Map F2 to compile and run the code in a terminal split
        vim.api.nvim_set_keymap('n', '<F2>', ':w<CR>:term!python3 %<CR>', { noremap = true, silent = true })
    end,
})

-- for Commenting
vim.api.nvim_set_keymap("n", "<C-s>", ":lua require('Comment.api').toggle.linewise.current()<CR>", { noremap = true, silent = true })
vim.api.nvim_set_keymap("i", "<C-s>", "<Esc>:lua require('Comment.api').toggle.linewise.current()<CR>i", { noremap = true, silent = true })
vim.api.nvim_set_keymap("v", "<C-s>", ":lua require('Comment.api').toggle.linewise(vim.fn.visualmode())<CR>", { noremap = true, silent = true })


-- Fuzzy Finder key binds
local builtin = require('telescope.builtin')
vim.keymap.set('n', '<leader>pf', function()
    require('telescope.builtin').find_files({
        hidden = true
    })
end, {})
vim.keymap.set('n', '<leader>ps', function()
    -- Prompt the user for input, and search using 'grep_string'
    local search_term = vim.fn.input("Grep > ")

    -- Call the Telescope built-in grep_string function
    require('telescope.builtin').grep_string({
        search = search_term, 
        -- Optionally, you can specify the directory or file types
        -- cwd = vim.fn.expand('%:p:h'),  -- search within the current file's directory
        -- follow = true,  -- follow symlinks (if necessary)
    })
end)

vim.keymap.set('i', 'jj', '<Esc>')


-- Harpoon configuration
local mark = require("harpoon.mark")
local ui = require("harpoon.ui")

vim.keymap.set("n", "<leader>a", mark.add_file)
vim.keymap.set("n", "<C-e>", ui.toggle_quick_menu)

vim.keymap.set("n", "<C-h>", function() ui.nav_file(1) end)
vim.keymap.set("n", "<C-j>", function() ui.nav_file(2) end)
vim.keymap.set("n", "<C-k>", function() ui.nav_file(3) end)
vim.keymap.set("n", "<C-l>", function() ui.nav_file(4) end)


-- Custom vim commands: 
vim.api.nvim_create_user_command('Sol', 'read ~/CP/sol.cpp', {})
vim.api.nvim_create_user_command('InitLua', 'e ~/.config/nvim/init.lua', {})
-- close tags

vim.cmd([[
  call plug#begin('~/.local/share/nvim/plugged')
  Plug 'alvan/vim-closetag'
  call plug#end()
  ]])

-- TODO : Optional configuration for vim-closetag
vim.g.closetag_filenames = '*.html,*.xhtml,*.phtml,*.js,*.jsx'
vim.g.closetag_filetypes = 'html,xhtml,phtml,javascript,typescript,typescriptreact,javascriptreact'

vim.cmd('colorscheme rose-pine')

-- vim.api.nvim_set_hl(0, "Normal", { bg = "NONE" })
-- vim.api.nvim_set_hl(0, "NonText", { bg = "NONE" })
-- vim.api.nvim_set_hl(0, "NormalFloat", { bg = "NONE" })
--
-- Set cursor shape to block in insert and normal modes
vim.opt.guicursor = {
  "n-v-c:block",          -- Normal, Visual, and Command-line modes: block cursor
  "i:block",              -- Insert mode: block cursor
  "r-cr:hor20",           -- Replace mode: horizontal line (optional, set to block if preferred)
  "sm:block"              -- Select mode: block cursor
}

