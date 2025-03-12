from markdown_it import MarkdownIt
from markdown_it.token import Token
from typing import List, Tuple

def is_chinese_text(text: str, threshold: float = 0.5) -> bool:
    """Check if the text contains Chinese characters above a certain threshold."""
    if not text.strip():
        return False
    chinese_chars = [char for char in text if '\u4e00' <= char <= '\u9fff']
    return (len(chinese_chars) / len(text)) > threshold
def parse_content(content: str) -> Tuple[List[str], List[Token]]:
    md = MarkdownIt()
    tokens = md.parse(content)
    translatable_texts = []
    elements = []
    
    for token in tokens:
        if token.type == 'inline':
            inline_elements = []
            for child in token.children:
                if child.type == 'text':
                    # Extract text for translation
                    translatable_texts.append(child.content)
                    # Keep the text token for reconstruction
                    inline_elements.append(child)
                else:
                    # Keep other tokens (formatting, links, etc.)
                    inline_elements.append(child)
            # Update the inline token's children
            token.children = inline_elements
            elements.append(token)
        else:
            # Keep other tokens
            elements.append(token)
    
    return translatable_texts, elements
