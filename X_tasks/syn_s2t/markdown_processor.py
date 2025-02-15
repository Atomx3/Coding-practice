import hashlib
from markdown_it import MarkdownIt

def generate_block_id(content):
    # Extract core content by removing whitespace and formatting
    core_content = ' '.join(content.strip().split())
    # Use first 50 chars for more stable but unique identification
    content_for_hash = core_content[:50]
    return hashlib.md5(content_for_hash.encode('utf-8')).hexdigest()

def parse_content_into_blocks(content, preserve_whitespace=False):
    md = MarkdownIt()
    tokens = md.parse(content)
    blocks = []
    current_block = {"content": "", "type": "", "whitespace_before": ""}
    
    whitespace_buffer = ""
    
    for token in tokens:
        if token.type in ['heading_open', 'list_item_open', 'fence', 'blockquote_open', 'table_open', 'paragraph_open']:
            if current_block["content"].strip():
                if preserve_whitespace:
                    current_block["whitespace_before"] = whitespace_buffer
                blocks.append(current_block)
            current_block = {"content": "", "type": token.type.replace('_open', ''), "whitespace_before": whitespace_buffer}
            whitespace_buffer = ""
            
        if token.type == 'inline':
            current_block["content"] += token.content + "\n"
            
        if token.type == 'softbreak':
            whitespace_buffer += "\n"
            
    if current_block["content"].strip():
        blocks.append(current_block)
        
    return blocks
