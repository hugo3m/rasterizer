/** @type {import('next').NextConfig} */
export default {
  webpack(config, { isServer }) {
    config.experiments = {
      ...config.experiments,
      asyncWebAssembly: true,
    };

    // tells webpack to take file ending in .data or .wasm
    config.module.rules.push({
      test: /\.(wasm|data)$/,
      type: 'asset/resource',
      generator: {
        filename: 'static/wasm/[name][ext]',
      },
    });

    return config;
  },
};