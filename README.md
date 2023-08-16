# stags - minimal static site generator

stags is a minimalist static site generator that relies on shell commands rather than a large templating language. stags also auto generates rss feeds

an example of a stags site is [my personal website](https://github.com/limnwiki/website)

## Dependencies
```
boost
```

the boost dependency can be removed by using the std::regex library in [`html.hpp`](/src/html.hpp), but the boost version is faster

## Installation
```sh
git clone https://github.com/limnwiki/stags.git
cd stags/build
make install
```

## File Structure
```
├── assets              static files
├── components          html components
├── data                markup files
├── pages               html pages
├── public              built site
└── stags.config.json   config file
```

## Templating
Templates are wrapped with 2 pairs of curly brackets
```html
<p> {{ "Hi" }} </p>
```

### Strings
strings are wrapped in double quotes
```html
<h1> Hello {{ "World" }} </h1>
```

### Variables
variables are accessed by their name. variables are defined in the `stags.config.json` file
```html
<h1> {{ site_url }} </h1>
```

### Template Strings
template strings are wrapped in single quotes and can embed variables into them with 1 pair of curly brackets
```html
<h1> {{ 'The site url is: {site_url}' }} </h1>
```

### Shell Commands
shell commands begins with a $ and takes in a string, template string, or variable as input. The output of the command is then added to the html
```html
<h1> {{ $ 'echo "Welcome to {site_url}!"' }} </h1>
```

### Components
components are reusable pieces of html that take in unlimited string parameters. Components are defined in the `components` directory and are accessed by their file name
```html
<!-- pages/index.html -->
<div> {{ Hello "John" "Doe" }} </div>
```
```html
<!-- components/Hello.html -->
<h1> Hello, {{ 1 }} {{ 2 }} </h1>
```

### That's it.
additional functionality can be added with the use of shell commands and scripts

## Markup Languages
stags does not support any markup languages out of the box but can be added using a tool like [pandoc](https://pandoc.org/)
- [great article about using markdown and html with pandoc](https://www.arthurkoziel.com/convert-md-to-html-pandoc/)

markup files are put in the `data` directory and are processed with the `data_processing_command` found in the config file

## Config
stags configuration is found in the `stags.config.json`
- `url`: site url
- `testing_url`: site url used for testing (ex. http://localhost:8000)
- `data_processing_command`: command used to process markup found in the `data` directory
- `variables`: dictionary of variables
- `rss_feeds`: array of rss feeds to generate
  - `title`: rss feed title
  - `description`: rss feed description
  - `file`: rss feed output file
  - `source`: rss feed source directory in `public` directory
  - `content_tag`: the html tag the rss feed content is found in (ex. `article`)
  - `include_index`: [true/false] (optional) include index.html files in rss feed
- `auto_routes`: [true/false] convert `file.html` to `file/index.html` when building the site
- `clear_public_directory`: [true/false] delete all files in `public` directory when rebuilding the site
