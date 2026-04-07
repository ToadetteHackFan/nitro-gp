#!/usr/bin/env python3
"""
Adjust the addresses in Code.map by adding an offset.
This makes the map addresses match the game addresses.
"""

import sys

def adjust_map_file(map_file, offset):
    """Add an offset to all addresses in the map file."""
    offset_int = int(offset, 16) if offset.startswith(('0x', '0X')) else int(offset)
    
    with open(map_file, 'r') as f:
        lines = f.readlines()
    
    output_lines = []
    for line in lines:
        # Skip header lines
        if line.startswith('Kamek') or line.startswith('  Offset') or line.strip() == '':
            output_lines.append(line)
            continue
        
        # Process lines with offset and size
        parts = line.split()
        if len(parts) >= 3:
            try:
                offset_hex = parts[0]
                size_hex = parts[1]
                rest = ' '.join(parts[2:])
                
                # Parse hex values
                offset_val = int(offset_hex, 16)
                size_val = int(size_hex, 16)
                
                # Add offset to the offset value
                new_offset_val = offset_val + offset_int
                
                # Format back to hex
                new_line = f"  {new_offset_val:08X} {size_val:06X} {rest}\n"
                output_lines.append(new_line)
            except ValueError:
                output_lines.append(line)
        else:
            output_lines.append(line)
    
    with open(map_file, 'w') as f:
        f.writelines(output_lines)
    
    print(f"Adjusted {map_file}: Added offset 0x{offset_int:X}")

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: adjust_map.py <map_file> [offset]")
        print("Default offset: 0x803992e0")
        sys.exit(1)
    
    map_file = sys.argv[1]
    offset = sys.argv[2] if len(sys.argv) > 2 else '0x803992e0'
    
    adjust_map_file(map_file, offset)
