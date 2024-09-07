const { createCanvas, loadImage } = require('canvas');
const fs = require('fs');
const path = require('path');

// Configuration
const INPUT_IMAGE = '../extras.png'; // Path to your input PNG image
const OUTPUT_DIR = '../keys'; // Directory where the chunks will be saved
const CHUNK_WIDTH = 32; // Size of each chunk (32x32)
const CHUNK_HEIGHT =  16;

// Create output directory if it doesn't exist
if (!fs.existsSync(OUTPUT_DIR)) {
    fs.mkdirSync(OUTPUT_DIR);
}

// Function to convert PNG buffer to XPM format
async function convertPngToXpm(pngBuffer, width, height) {
    const canvas = createCanvas(width, height);
    const ctx = canvas.getContext('2d');
    return new Promise((resolve, reject) => {
        loadImage(pngBuffer).then(image => {
            ctx.drawImage(image, 0, 0, width, height);
            const imageData = ctx.getImageData(0, 0, width, height);
            const pixels = new Uint8Array(imageData.data);

            // Create a map for unique colors
            const colorMap = new Map();
            const colors = [];
            const pixelArray = [];

            // Helper function to convert RGBA to a hex string
            const rgbaToHex = (r, g, b, a) => {
                return a === 0 ? 'None' : `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}`;
            };

            // Generate a unique single-character code for each color
            const colorChars = ' .,-:+;=!?[]{}()*&^%$#0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz';
            let colorCounter = 0;

            for (let i = 0; i < pixels.length; i += 4) {
                const r = pixels[i];
                const g = pixels[i + 1];
                const b = pixels[i + 2];
                const a = pixels[i + 3];

                const color = rgbaToHex(r, g, b, a);
                if (!colorMap.has(color)) {
                    if (colorCounter < colorChars.length) {
                        colorMap.set(color, colorChars[colorCounter]);
                        colors.push({ char: colorChars[colorCounter], hex: color });
                        colorCounter++;
                    } else {
                        return reject(new Error(`Too many colors for XPM format. Max allowed is ${colorChars.length}.`));
                    }
                }
                pixelArray.push(colorMap.get(color));
            }

            // Check if the chunk is completely empty
            if (!pixelArray.some(char => char !== ' ')) {
                return resolve(null); // Return null to indicate an empty chunk
            }

            // Create XPM colors
            const header = [
                '/* XPM */',
                'static char *item_xpm[] = {',
                `"${width} ${height} ${colors.length} 1",`
            ];

            colors.forEach(color => {
                header.push(`"${color.char} c ${color.hex}",`);
            });

            header.push('/* pixels */');

            // Create XPM pixel data
            for (let i = 0; i < height; i++) {
                const row = [];
                for (let j = 0; j < width; j++) {
                    if(pixelArray[i * width + j] == ' '){
                        row.push('@');
                        continue;
                    }
                    row.push(pixelArray[i * width + j]);
                }
                header.push(`"${row.join('')}",`);
            }

            header.push('"};');
            resolve(header.join('\n'));
        }).catch(reject);
    });
}
// Function to split image into chunks
async function splitImage() {
    try {
        // Load the image
        const image = await loadImage(INPUT_IMAGE);
        const { width, height } = image;
        console.log(`Image dimensions: ${width}x${height}`);

        let chunkId = 0; // Initialize chunk counter

        // Process each chunk
        for (let y = 0; y < height; y += CHUNK_HEIGHT) {
            for (let x = 0; x < width; x += CHUNK_WIDTH) {
                // Calculate the chunk dimensions and bounds
                const chunkWidth = Math.min(CHUNK_WIDTH, width - x);
                const chunkHeight = Math.min(CHUNK_HEIGHT, height - y);

                // Skip if chunk dimensions are not valid
                if (chunkWidth <= 0 || chunkHeight <= 0) {
                    console.warn(`Skipping invalid chunk at (${x}, ${y})`);
                    continue;
                }

                // Create a new canvas for the chunk
                const canvas = createCanvas(chunkWidth, chunkHeight);
                const ctx = canvas.getContext('2d');

                // Draw the chunk onto the canvas
                ctx.drawImage(image, x, y, chunkWidth, chunkHeight, 0, 0, chunkWidth, chunkHeight);

                // Create output filename
                const outputFilename = path.join(
                    OUTPUT_DIR,
                    `key${chunkId}.xpm`
                );

                // Convert chunk to PNG buffer
                const pngBuffer = canvas.toBuffer('image/png');
                // Convert PNG buffer to XPM format
                const xpmData = await convertPngToXpm(pngBuffer, chunkWidth, chunkHeight);

                // Skip saving if XPM data is null (empty chunk)
                if (xpmData === null) {
                    console.log(`Skipping empty chunk at (${x}, ${y})`);
                    continue;
                }

                // Save the XPM chunk
                fs.writeFileSync(outputFilename, xpmData);
                console.log(`Saved chunk: ${outputFilename}`);

                chunkId++; // Increment chunk counter
            }
        }

        console.log('Image splitting complete!');
    } catch (error) {
        console.error('Error splitting image:', error);
    }
}


// Execute the function
splitImage();
